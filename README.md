# TerminalStream
This project is intended to create an Ngrok based solution to showing off terminal apps in the same way one would demo their website projects with Ngrok or any other tunneling app/service.<br>

The shell used in the browser makes use of the XTermJS library while the remote shell that hosts the terminal project is a rework of my old 42 Minishell project.

Only static apps (with simple input/output) are handled. Support for projects that make use of `ncurses` or have their own enviroments (like shells or docker projects) are for future releases--if pulling that off is even possible. 

## Quickstart
You can instantly get the project running by running
```
python3 run.py
```
at the root of the project. The default password is `apples123`.<br>
Ideally, read the below to get a better idea how how to use this project before doing this :).

## Getting Start Locally
Navigate to `Server/`.
Before initializing the local servers for each of your projects, you'll have to configure the `config.json` file with your projects specs in the following JSON format 
```
{
	"url": "127.0.0.1", # The address of the webserver that users will be able to visit to try your stuff
	"author": "AlysonBee", # The owner of the targeted repo
	"Bigquery_Schema_Autogen": { # the first project URL and the port you want to expose for it
	    "link": "https://github.com/AlysonBee/Python_BigQuery_Schema_Autogen",
	    "port": 4242
	},
	"OSX_Packer": { # the second project URL and the port to expose for it
	    "link": "https://github.com/AlysonBee/OSX_Packer",
	    "port": 5555
	}
  ...
}
```
You can add as many projects as you want with the key being the name of the project with its values following the same paradigm as shown above.

Once you've set up your `config.json` file, all that's left to do is host your projects with a simple
```
python3 init.py activate
```
And that's it for a local setup.

## The Webserver
Navigate to `Client/`.
All you have to do is ensure that the webserver is running at the same url as the one specified in your `url` variable in your config file, then simply run
```
python3 app.py
```
And visit the URL.
<img src="Client/screenshots/setupscreen.png" />

The password can be found in the `validate.json` file (it's default is `apples123`)<br><br> On your first ever visit (with a clean database of course) you'll be greeted with this page.
All you need to do is upload the same `config.json` file you created in the previous step and that's it. Your projects will appear as a list on the next page.
<img src="Client/screenshots/ilsting.png"/>
Click on "View" project and try it out.

## When you're finsihed
Don't forget to run 
```
python3 init.py deactivate
```
on your local machine. This will kill the daemon processes showing off your project. Coz open ports is bad hygene and we must always always always wash our hands after handshakes :).

## Using the project alonside Ngrok
Run Ngrok the same way you normally would and share the URL with whoever you're showing your project to and they can give it a go straight from the website.

## Next Steps
- The shell hosted locally is completely insecure and needs to be extensively customized to prevent users from having remote access to your entire filesystem. This is just a demo.
- The website needs a lot of work (a looooooot of work). It's recycled from an old version but this functionality is relatively okay.
- I think that's about it. Cheers

## Important
This project is intended to create an Ngrok based solution to showing off terminal apps in the same way one would demo their website. It's important that should you wish to add some projects to be usable for public purposes (demos, hackathons, CV links etc), it's advised that you host the `Server` in a secure cloud virtual machine or Docker container. The built-in shell for interacting with projects is relatively minimal but safety first is advised for the possiblity multiple users.

### AlysonBee











