# Printing from Python to the browser console

This example includes a typical main() entry point that initializes the Python
interpreter. It then runs a single line of Python code, printing a message.
This message should appear on the browser's console (part of the development
tools that come with many browsers).

# Building

Run ```make```.

# Running

Run ```make serve``` to start a web server on local port 8062 (this requires
Python) and then visit the test page
[http://localhost:8062/](http://localhost:8062/).

It will take a while to start up as only limited attempts have been made at
reducing the initial file system. Once it has started go to the developer
console and you should see some output.