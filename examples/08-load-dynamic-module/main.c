#include <stdlib.h>
#include <stdio.h>
#include <emscripten.h>
#include <Python.h>
#include <dlfcn.h>

int runpython(char *str) {
    printf("%s", str);
    return PyRun_SimpleString(str);
    }

int main(int argc, char** argv) {

    setenv("PYTHONHOME", "/", 0);

    fprintf(stderr, "Initializing...\n");

    Py_InitializeEx(0);

    void *result = dlopen("/libpython3.5.js", 0);

    if(result == NULL)
        fprintf(stderr, "Failed: %s\n", dlerror());
    else
        fprintf(stderr, "Successfully loaded the DLL!\n");

    fprintf(stderr, "Home directory: %s\n", Py_GetPythonHome());

    emscripten_exit_with_live_runtime();
    return 0;
}
