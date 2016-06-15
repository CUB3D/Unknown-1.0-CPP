#include "stdafx.h"
#include "PythonScript.h"
#include "Python.h"

void Unknown::Python::checkError(PyObject* obj)
{
    if(obj == NULL)
    {
        PyErr_Print();
        exit(0);
    }
}

void Unknown::Python::init()
{
    Py_Initialize();

    PyObject* moduleSys = PyImport_ImportModule("sys");
    checkError(moduleSys);
    PyObject* sysModulePath = PyObject_GetAttrString(moduleSys, "path");
    checkError(sysModulePath);
    PyList_Append(sysModulePath, PyUnicode_FromString("."));
    //TODO: importing dynamicaly
}
