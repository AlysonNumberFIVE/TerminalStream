var response = "";
var history = 0;

function print_output(response, term) {
	if (response.includes('\n') == true)
	{
		var values = response.split('\n');
		var i;
		for (i = 0; i < values.length; i++) {
			console.log('here');
			term.write("\r\n"+ values[i]);
		}
	}
	else
	{
		console.log('default');
		term.write("\r\n"+response);
	}
}

function shell_control(x, term) {
	var buffer = {};
	$.ajax(
	{
		type: 'POST',
		url: '/check',
		data: {'value': x},
		contentType: "application/json",
		success: function(data) {
			console.log('>> ',data)
			buffer = data;
			if (buffer["value"].length > 0)
			{
				response = buffer["value"].replace(/\u21B5/g,'\n');
				print_output(response, term);
			}
			term.write("\r\nweb shell $ ");
		},
		error: function(data) {
			console.log(data)
		}
	});

}


var term = new Terminal({
	cursorBlink: "block"
});

var curr_line = ""
var entries = []
term.open(document.getElementById("terminal"));

term.write("web shell $ ");
term.prompt = () => {
	if (curr_line) {
		let data = {method: "command", command: curr_line};
		ws.send(JSON.stringify(data));
	}
};
term.prompt();
term.on("key", function(key, ev) {

	if (ev.keyCode == 13) {
		if (curr_line.length > 1)
		{
			entries.push(curr_line);
			shell_control(curr_line, term);
		}
		else 
			term.write('\r\nweb shell $ ');
		curr_line = ""
		response = "";
		term.prompt();
	} else if (ev.keyCode == 8) {
		if (curr_line && term.buffer.cursorX > 12) {
			curr_line = curr_line.slice(0, curr_line.length - 1);
			term.write("\b \b");
		}
	} else if (ev.keyCode == 38) {
		staticvalue = term.buffer.cursorY;
		term.buffer.cursorY = staticvalue;
	} else if (ev.keyCode == 40) {
		staticvalue = term.buffer.cursorY;
		term.buffer.cursorY = term.buffer.cursorY;
	} else if (ev.keyCode == 37) {
		console.log('term.buffer.cursorY ', term.buffer.cursorX);
	} else if (ev.keyCode == 39) {
		console.log('term.buffer.cursorY ', term.buffer.cursorX)
	} else {
		curr_line += key;
		term.write(key);
	}
});
