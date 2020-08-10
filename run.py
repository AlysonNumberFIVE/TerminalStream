import os
import sys

os.chdir(os.path.join(os.getcwd(), "Server"))
os.system("python3 init.py activate")
os.chdir(os.path.join(os.getcwd(), "..", "Client"))
os.system("python3 app.py")
