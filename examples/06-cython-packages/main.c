#include <stdlib.h>
#include <stdio.h>

#include <emscripten.h>
#include <Python.h>

#include "builtins.h"


static void onload(const char *filename) {
    printf("Loaded %s.\n", filename);
    PyRun_SimpleString(
        "import zipfile;"
        "zipfile.ZipFile('/app.zip').extractall('/');"
    );
    PyRun_SimpleString(
        "import sys;"
        "sys.path.insert(0, '/');"
    );
    PyRun_SimpleString(
        "import runpy;"
        "runpy.run_module('app');"
    );
}


static void onloaderror(const char *filename) {
    printf("Failed to load %s, aborting.\n", filename);
    PyRun_SimpleString("print('fail')");
}


int main(int argc, char** argv) {
    setenv("PYTHONHOME", "/", 0);

    PyImport_ExtendInittab(builtins);

    Py_InitializeEx(0);

    PyRun_SimpleString(
        "import importlib.abc\n" \
        "import importlib.machinery\n" \
        "import sys\n" \
        "\n" \
        "\n" \
        "class Finder(importlib.abc.MetaPathFinder):\n" \
        "    def find_spec(self, fullname, path, target=None):\n" \
        "        if fullname in sys.builtin_module_names:\n" \
        "            return importlib.machinery.ModuleSpec(\n" \
        "                fullname,\n" \
        "                importlib.machinery.BuiltinImporter,\n" \
        "            )\n" \
        "\n" \
        "\n" \
        "sys.meta_path.append(Finder())\n" \
    );

    // Fetch app.zip from the server.
    emscripten_async_wget("app.zip", "/app.zip", onload, onloaderror);

    emscripten_exit_with_live_runtime();
    return 0;
}
