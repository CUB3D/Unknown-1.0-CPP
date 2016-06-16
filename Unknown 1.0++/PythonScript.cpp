#include "stdafx.h"
#include "PythonScript.h"
#include "Python.h"

Unknown::Python::Interperator* ::Unknown::Python::instance = NULL;

void Unknown::Python::Interperator::checkError(PyObject* obj)
{
    if(obj == NULL)
    {
        PyErr_Print();
        exit(0);
    }
}

void Unknown::Python::Interperator::importModule(std::string name)
{
    PyObject* sysModulePath = PyObject_GetAttrString(this->moduleSys, "path");
    checkError(sysModulePath);
    PyList_Append(sysModulePath, PyUnicode_FromString("."));
 
}

void Unknown::Python::Interperator::init()
{
    Py_Initialize();

    this->moduleSys = PyImport_ImportModule("sys");
    checkError(this->moduleSys);
}

Unknown::Python::Interperator* Unknown::Python::getInterperator()
{
    if(instance == NULL)
    {
        instance = new Interperator();
    }
    return instance;
}
