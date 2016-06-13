#include "stdafx.h"
#include "PythonScript.h"
#include "Python.h"

void Unknown::Python::init()
{
    Py_Initialize();

    PyObject* moduleSys = PyImport_ImportModule("sys");
    //checkPythonError(moduleSys);
    PyObject* sysModulePath = PyObject_GetAttrString(moduleSys, "path");
    //checkPythonError(sysModulePath);
    PyList_Append(sysModulePath, PyUnicode_FromString("."));
    //TODO: importing dynamicaly
}
