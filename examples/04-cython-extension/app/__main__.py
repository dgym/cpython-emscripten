import json

import js


message = "Success - the app is running: {}".format(__file__)
code = '''
let node = document.createElement('br');
document.body.appendChild(node);

node = document.createTextNode({});
document.body.appendChild(node);
'''.format(json.dumps(message))
js.run(bytes(code, 'utf8'))
