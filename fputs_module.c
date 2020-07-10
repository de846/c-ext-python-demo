#include <Python.h>

static PyObject *method_fputs(PyObject *self, PyObject *args) {

    /* a PyObject is an object structure that is used to define
    object types for Python that has many common fields. All
    objects types extend this one.

    When this method is actually invoked, the program parses arguments
    in PyArg_ParseTuple() below and passes them to fputs(), then returns the
    value from PyLong_FromLong(). */

    char *str = NULL;
    char *filename = NULL;
    int bytes_copied = -1;
    unsigned long min_str_len = 3;
    /* PyArg_ParseTuple passes arguments from Python into C.
    'args' are a PyObject type, 'ss' is a format specifier.
    &str and &filename are pointer references to local C vars. */

    if (!PyArg_ParseTuple(args, "ss", &str, &filename)) {
        return NULL;
    }

    if (strlen(str) < min_str_len) {
        PyErr_SetString(PyExc_ValueError, "String length must be greater than 3");
        return NULL;
    }
    FILE *fp = fopen(filename, "w");
    bytes_copied = fputs(str, fp);
    fclose(fp);

    /* The PyLong_FromLong method returns a PyLongObject which
    Python represents as an int. */

    return PyLong_FromLong(bytes_copied);
}



// Initialization Functions
/* The Python interpreter learns about our defined methods through the
PyMethodDef object. We use an array so we could define more than one function */

static PyMethodDef FputsMethods[] = {
    {"fputs", method_fputs, METH_VARARGS, "Python method interface for fputs C library function"},
    {NULL, NULL, 0, NULL}
    /* Structure:
    "fputs" is the method name python would invoke
    method_fputs is the C function that will be invoked
    METH_VARARGS is a flag that Python interpreter to accept two PyObject*
        args, self (the module object) and args (a tuple with the args).
    The string is the method's docstring. */
};

static struct PyModuleDef fputsmodule = {
    PyModuleDef_HEAD_INIT,
    "fputs",
    "Python module for fputs C library function",
    -1,
    FputsMethods
    /* Structure:
    PyModuleDef_HEAD_INIT is a member of PyModuleDef_Base
    "fputs" is the name of Python C Extension module
    The string is the _module_ docstring
    -1 is the memory needed to store program state, with -1
        meaning that no sub-interpreter support is provided
    FputsMethods is the reference to the method table above. */
};

PyMODINIT_FUNC PyInit_fputs(void) {
    PyObject *module = PyModule_Create(&fputsmodule);

    /* This method is called when Python imports the above defined
    module for the first time. When the return type is PyMODINIT_FUNC,
    it does:
        1. Sets return type implicitly as PyObject *
        2. Declares any special linkages
        3. Declares the function as an extern "C".
    PyModule_Create() returns a new module object of PyObject* type. The
    argument requires the address (hence the '&') of the module structure
    we defined above. We store the module in a PyObject *module entity. */

    // define a constant to be available to python
    PyModule_AddIntConstant(module, "C_INT_CONSTANT", 16);

    // define a macro to be added
    #define C_MACRO 256

    // attach macro to module
    PyModule_AddIntMacro(module, C_MACRO);

    return module;
}

/* When Python imports our module, it first calls PyInit_fputs(), which calls
PyModule_Create with our module address. This inits a PyModuleDef, which inits
the PyMethod_Def array. A refernce to the module object is returned to the
Python interpreter.*/
