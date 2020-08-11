import os
import json
import sys
import signal

from flask import url_for
from flask import render_template
from flask import jsonify
from flask import Flask
from flask import request
from flask import redirect
from flask_wtf import FlaskForm
from flask_sqlalchemy import SQLAlchemy
from flask_migrate import Migrate
from wtforms import SubmitField

from python_version import GoldiloxAPIClientConnection

APIsocket = None
SocketList = list()
flag = False

app = Flask(__name__)
url = '127.0.0.1'
basedir = os.path.abspath(os.path.dirname(__file__))

class Config(object):
	SQLALCHEMY_DATABASE_URI = 'sqlite:///' + os.path.join(basedir, 'app.db')
	SQLALCHEMY_TRACK_MODIFICATION = False

app.config.from_object(Config)
app.config['UPLOAD_FOLDER'] = os.path.join(basedir, 'upload')
app.config['SECRET_KEY'] = 'ISUPPOSE'
db = SQLAlchemy(app)
migrate = Migrate(app, db)

class SendButton(FlaskForm):
	"""Login Form and whatever."""
	button = SubmitField('CHANGE CONFIG')



class Project(db.Model):
	"""Project class."""
	id = db.Column(db.Integer, primary_key=True)
	port = db.Column(db.Integer, is_unique=True)
	project_name = db.Column(db.String(4986))
	github_link = db.Column(db.String(12096))
	author = db.Column(db.String(4096))




def kill_server(first, second):
	string = os.path.join(os.getcwd(), "..", "Server")
	os.chdir(string)
	os.system("python3 init.py deactivate")
	sys.exit(1)

signal.signal(signal.SIGINT, kill_server)


@app.route('/check', methods=['GET', 'POST'])
def new():
	"""The route that's hit when a terminal command is sent."""
	values = request.get_data().decode('utf-8').split('=')
	to_send = values[1].replace('%20', ' ').replace('%2F', '/')
	APIsocket.Send(to_send)
	ret = APIsocket.Recv()
	return jsonify({'value': ret})


def handle_config(content: str):
	"""Handle the creation of projects to display.

	:content: The JSON payload with the project info.
	"""
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
	"""Handle the uploading of config files."""
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
	global flag
	if flag is False:
		return redirect(url_for('login'))
#	is_connected()
	allprojects = Project.query.all()

	flag = False
	if len(allprojects):
		for project in allprojects:
			db.session.delete(project)
			db.session.commit()
	return render_template('setup.html')	


def check_socket_object(SocketList: list, port: int):
	"""Check if the port named is currently open.

	:SocketList: The list of all the connected projects.
	:port: The port number to verify and establish a
		connection against.
	"""
	global APIsocket

	for Socket in SocketList:
		if Socket['port'] == port:
			APIsocket = Socket['socket']
			return True
	return False


@app.route('/tryitout/<project_name>')
def tryitout(project_name: str):
	"""Endpoint for tryign out a project.
	
	:param: The name of the project.
	"""
	projects = Project.query.all()
	found = None
	global APIsocket
	global SocketList

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
	return render_template('review.html', project=found) 


@app.route('/', methods=['GET', 'POST'])
def test():
	"""The list of all projects currently on display."""
	all_projects = Project.query.all()

	if len(all_projects) == 0:
		return redirect(url_for('setup'))

	return render_template('msgboard.html',
							projects=all_projects)


def validate_user(submitted:str):
	"""Temporary workaround for validating a password.

	:submitted: The password submitted by the user.
	:return: True if the password is correct and
		False otherwise.
	"""
	try:
		value = open('validate.json').read()
	except FileNotFoundError:
		return False
	content = json.loads(value)
	psswd = content['password']
	if submitted == psswd:
		return True
	return False


@app.route('/login', methods=['GET', 'POST'])
def login():
	"""The permission page to verify that user can upload config."""
	submit = SendButton()
	global flag
	error = False
	if submit.validate_on_submit():
		password = request.form['password']
		if validate_user(password) is True:
			flag = True
			return redirect(url_for('setup'))
		error = True
	return render_template('login.html',
		button=submit,
		error=error
	)


def delete_all():
	"""Clear all projects."""
	allprojects = Project.query.all()
	for project in allprojects:
		db.session.delete(project)
		db.session.commit()


if __name__ == '__main__':
	app.run()



