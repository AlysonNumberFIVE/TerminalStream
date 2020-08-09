import os
import json

from flask import url_for
from flask import render_template
from flask import jsonify
from flask import Flask
from flask import request
from flask import redirect
from flask_sqlalchemy import SQLAlchemy
from flask_migrate import Migrate

from python_version import GoldiloxAPIClientConnection

APIsocket = None

SocketList = list()

app = Flask(__name__)
url = '127.0.0.1'
basedir = os.path.abspath(os.path.dirname(__file__))

#APIsocket = GoldiloxAPIClientConnection('127.0.0.1', 4242)
class Config(object):
	SQLALCHEMY_DATABASE_URI = 'sqlite:///' + os.path.join(basedir, 'app.db')
	SQLALCHEMY_TRACK_MODIFICATION = False

app.config.from_object(Config)
app.config['UPLOAD_FOLDER'] = os.path.join(basedir, 'upload')
db = SQLAlchemy(app)
migrate = Migrate(app, db)


class Project(db.Model):
	"""Project class."""
	id = db.Column(db.Integer, primary_key=True)
	port = db.Column(db.Integer, is_unique=True)
	project_name = db.Column(db.String(4986))
	github_link = db.Column(db.String(12096))
	author = db.Column(db.String(4096))


def is_connected():
	global APIsocket
	if APIsocket is not None:
		APIsocket.Close()
		APIsocket = None


@app.route('/check', methods=['GET', 'POST'])
def new():
	values = request.get_data().decode('utf-8').split('=')
	to_send = values[1].replace('%20', ' ').replace('%2F', '/')
	APIsocket.Send(to_send)
	ret = APIsocket.Recv()
	return jsonify({'value': ret})




def handle_config(content: str):
	global url

	count = 0
	json_content = json.loads(content)
	url = json_content['url']
	author = json_content['author']
	for k, v in json_content.items():
		if count > 1:
			project = Project(
				port = int(json_content[k]['port']),
				project_name = k,
				github_link = json_content[k]['link'],
				author = author
			)
			db.session.add(project)
			db.session.commit()
		count += 1

@app.route('/upload', methods=['GET', 'POST'])
def upload():

	if request.method == 'POST':
		f = request.files['file']
		f.save(os.path.join(app.config['UPLOAD_FOLDER'], f.filename))
		content = open(
			os.path.join(app.config['UPLOAD_FOLDER'], f.filename)
		).read()
		print(content)
		handle_config(content)
		return redirect(url_for('test'))


@app.route('/setup')
def setup():
#	is_connected()
	allprojects = Project.query.all()

	if len(allprojects):
		for project in allprojects:
			db.session.delete(project)
			db.session.commit()
	return render_template('setup.html')	


def check_socket_object(SocketList: list, port: int):
	global APIsocket

	for Socket in SocketList:
		if Socket['port'] == port:
			APIsocket = Socket['socket']
			return True
	return False

@app.route('/tryitout/<project_name>')
def tryitout(project_name: str):
	projects = Project.query.all()
	found = None
	global APIsocket
	global SocketList

	print('success')
	for project in projects:
		if project.project_name == project_name:
			found = project
			break

	if found is not None and check_socket_object(SocketList, found.port) is False:
		APIsocket = GoldiloxAPIClientConnection(
			url,
			found.port
		)
		socket_object = {
			'socket': APIsocket,
			'url': url,
			'port': found.port
		}
		SocketList.append(socket_object)
		print('APISocket')
	return render_template('review.html', project=found) 


@app.route('/', methods=['GET', 'POST'])
def test():
#	is_connected()
	all_projects = Project.query.all()

	if len(all_projects) == 0:
		return redirect(url_for('setup'))

	return render_template('msgboard.html',
							projects=all_projects)


def delete_all():
	allprojects = Project.query.all()
	for project in allprojects:
		db.session.delete(project)
		db.session.commit()
	print("deleted")

delete_all()

if __name__ == '__main__':
	app.run()



