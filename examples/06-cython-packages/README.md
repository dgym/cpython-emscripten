# Cython modules in packages

This example shows how Cython modules can be linked with Python and made
available as built in modules.

There are currently two complications with doing this:

 - If the module is in a package Cython drops the package information.
 - Python does not handle built in modules which are in a package.
 
The first issue is resolved by editing Cython's output to add package
information.
The first step is to give the init function a unique name based on the
package, otherwise conflicts may occur.
The second is to replace the module name with its full path.
Both steps are handled by the patch_cython_module.py script in utils/.

The second issue is resolved by adding a custom import hook that recognises
built in modules and handles them correctly. This is done in main.c using
some Python code.

Currently only Python 3 is supported, although the techniques may be applicable
to a 2.7 build.


# Building

Run ```make```.

# Running

Run ```make serve``` to start a web server on local port 8062 (this requires
Python) and then visit the test page
[http://localhost:8062/](http://localhost:8062/).
