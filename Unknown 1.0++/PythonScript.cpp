#include "stdafx.h"
#include "PythonScript.h"
#include "Python.h"

void Unknown::Python:Script:::checkError(PyObject* obj)
{
    if(obj == NULL)
    {
        PyErr_Print();
        exit(0);
    }
}

void Unknown::Python::Script::importModule(std::string name)
{
    PyObject* sysModulePath = PyObject_GetAttrString(getInterperator()->moduleSys, "path");
    checkError(sysModulePath);
    PyList_Append(sysModulePath, PyUnicode_FromString("."));
 
}

void Unknown::Python::Interperator::init()
{
    Py_Initialize();

    this->moduleSys = PyImport_ImportModule("sys");
    checkError(this->moduleSys);
}
