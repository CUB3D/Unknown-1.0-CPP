#include "stdafx.h"
#include "PythonScript.h"
#include "Python.h"
#include "Log.h"

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
    this->addSearchPath(".");
}

Unknown::Python::Interpreter* Unknown::Python::getInterpreter()
{
    if(instance == NULL)
    {
        instance = new Interpreter();
    }
    return instance;
}

void Unknown::Python::Interpreter::loadScript(std::string name)
{
    UK_LOG_INFO(::Unknown::concat({"Loading script ", name.c_str()}).c_str());
    PyObject* testModule = PyImport_ImportModule(name.c_str());
    checkError(testModule);
    PyObject* initFunction = PyObject_GetAttrString(testModule, "init");
    if(initFunction)
    {
        PyObject_CallObject(initFunction, NULL);
    }
}