
import json

from flask import url_for
from flask import render_template
from flask import jsonify
from flask import Flask
from flask import request
from flask_socketio import SocketIO
from flask_socketio import emit

from python_version import GoldiloxAPIClientConnection


app = Flask(__name__)

APIsocket = GoldiloxAPIClientConnection('127.0.0.1', 4242)
"""
def client():

	conn = GoldiloxAPIClientConnection('127.0.0.1', 4242)

	print('Here again')
	while True:
		buffer = input('Say something : ')
		print('here')
		conn.Send(buffer)
		print('again')
		buffer = conn.Recv()
		print(f'buffer is {buffer}')
"""

@app.route('/check', methods=['GET', 'POST'])
def new():
	print(dir(request))
	values = request.get_data().decode('utf-8').split('=')
	print('valuse ', values)
	print('asdfasd ', request.get_data().decode('utf-8'), " as0dgjasd")
	print('valuse 1 is ', values[1])
	to_send = values[1].replace('%20', ' ')
	APIsocket.Send(to_send)
	ret = APIsocket.Recv()

	return jsonify({'value': ret})


@app.route('/', methods=['GET', 'POST'])
def test():
	return render_template('helloxterm.html')


if __name__ == '__main__':
	app.run()



