
import os
import json
import sys

content = open('config.json').read()
json_content = json.loads(content)
count = 0

if len(sys.argv) == 2 and sys.argv[1] == 'activate':
	os.system('make all')
	os.system('mkdir projects')
	url = json_content['url']
	author = json_content['author']
	for k, v in json_content.items():
		if count > 1:
			os.system(f'git clone {json_content[k]['link']} projects/{k}')
			os.system(f'cp server projects/{k}')
			os.system(f'.projects/{k}/server {json_content[k]['port']}')
		count += 1

elif len(sys.argv) == 2 and sys.argv[1] == 'deactivate':
	os.system('make clean')
	for k, v in json_content.items():
		if count > 1:
			os.system("kill $(ps aux | grep 'projects/{}server' | awk '{print $2}')".format(
				k)
			)
		count += 1
	os.system('rm -rf projects')

else:
	print('Usage: python3 init.py activate/deactivate')







