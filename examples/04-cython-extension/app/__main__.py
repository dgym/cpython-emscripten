import json

import js


message = "The app is running: {}".format(__file__)
code = '''
var node = document.createTextNode({});
document.body.appendChild(node);
'''.format(json.dumps(message))
js.run(bytes(code, 'utf8'))
