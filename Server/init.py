
import os
import json
import sys
import signal
import subprocess as sub


try:
	content = open('config.json').read()
except:
	print('Error: config file missing')
	sys.exit(1)

json_content = json.loads(content)
count = 0

if len(sys.argv) == 2 and sys.argv[1] == 'activate':
	os.system('make server')
	os.system('mkdir projects')
	url = json_content['url']
	author = json_content['author']
	for k, v in json_content.items():
		if count > 1:
			os.system(f"git clone {json_content[k]['link']} projects/{k}")
			os.system(f'cp .server projects/{k}')
			os.system(f"./projects/{k}/.server {json_content[k]['port']} {k}")
		count += 1

elif len(sys.argv) == 2 and sys.argv[1] == 'deactivate':
	os.system('make fclean')
	os.system('rm -rf projects')
	for k, v in json_content.items():
		if count > 1:
			system_string = "lsof -i4TCP:"+str(json_content[k]['port'])+ "| grep LISTEN | awk \'{ print $2}\' | awk xargs"
			proc = sub.Popen(['ps', '-A'], stdout=sub.PIPE, stderr=sub.PIPE)
			out, err = proc.communicate()
			os.system(system_string)
			for line in out.splitlines():
				if f"./projects/{k}/.server" in str(line):
					pid = int(line.split(None, 1)[0])
					os.kill(pid, signal.SIGKILL)

		count += 1
	os.system('rm -rf projects')

else:
	print('Usage: python3 init.py activate/deactivate')







