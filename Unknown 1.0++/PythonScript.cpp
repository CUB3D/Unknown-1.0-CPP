#include "stdafx.h"
#include "PythonScript.h"
#include "Python.h"

Unknown::Python::Interpreter* ::Unknown::Python::instance = NULL;

void Unknown::Python::Interpreter::checkError(PyObject* obj)
{
    if(obj == NULL)
    {
        PyErr_Print();
        exit(0);
    }
}

void Unknown::Python::Interpreter::addSearchPath(std::string name)
{
    PyObject* sysModulePath = PyObject_GetAttrString(this->moduleSys, "path");
    checkError(sysModulePath);
    PyList_Append(sysModulePath, PyUnicode_FromString(name.c_str()));
}

void Unknown::Python::Interpreter::init()
{
    Py_Initialize();

    this->moduleSys = PyImport_ImportModule("sys");
    checkError(this->moduleSys);
}

Unknown::Python::Interpreter* Unknown::Python::getInterpreter()
{
    if(instance == NULL)
    {
        instance = new Interpreter();
    }
    return instance;
}
