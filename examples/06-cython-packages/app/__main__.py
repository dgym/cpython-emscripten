import js
js.run(b'''
window.output = function (line) {
    document.getElementById('output').appendChild(
        document.createTextNode(line)
    );
}
''')


js.run(b'output("Imported top level module: success\\n");')


js.run(b'output("Importing absolute package module a: ");')
try:
    import app.a
except ImportError:
    js.run(b'output("failed\\n");')
else:
    js.run(b'output("success\\n");')


js.run(b'output("Importing relative package module b: ");')
try:
    from . import b
except ImportError:
    js.run(b'output("failed\\n");')
else:
    js.run(b'output("success\\n");')


js.run(b'output("Importing nested relative modules c: ");')
try:
    from . import c
except ImportError:
    js.run(b'output("failed\\n");')
else:
    js.run(b'output("success\\n");')
