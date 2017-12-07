#include "stdafx.h"
#include "PythonScript.h"
#include <Python.h>
#include "Log.h"
#include "Unknown.h"
#include <cstdio>

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

PyMethodDef* generatePyMethodDef(std::string functionName, PyCFunction implementation, std::string doc)
{
    PyMethodDef* definition = (PyMethodDef*) malloc(sizeof(*definition));
    definition->ml_name = functionName.c_str();
    definition->ml_meth = implementation;
    definition->ml_flags = METH_VARARGS;
    definition->ml_doc = doc.c_str();

    return definition;
}

PyObject* generatePyCallable(std::string moduleName, PyMethodDef* methodDefinition)
{
    PyObject* moduleNamePyString = PyUnicode_FromString(moduleName.c_str());
Unknown::Python::getInterpreter()->checkError(moduleNamePyString);
    PyObject* callable = PyCFunction_NewEx(methodDefinition, (PyObject*)NULL, moduleNamePyString);
    Unknown::Python::getInterpreter()->checkError(callable);

    return callable;
}

void createMethod(std::string moduleName, PyObject* callable, std::string functionName)
{
    PyObject* moduleNameString = PyUnicode_FromString(moduleName.c_str());
    PyObject* module = PyImport_Import(moduleNameString);
    Unknown::Python::getInterpreter()->checkError(module);
    PyObject* originalDict = PyModule_GetDict(module);
    Unknown::Python::getInterpreter()->checkError(originalDict);
    PyDict_SetItemString(originalDict, functionName.c_str(), callable);
}

void registerMethod(std::string moduleName, std::string functionName, std::string functionDescription, PyCFunction callback)
{
    PyMethodDef* methodDefinition = generatePyMethodDef(functionName, callback, functionDescription);
    PyObject* callable = generatePyCallable(moduleName, methodDefinition);
    createMethod(moduleName, callable, functionName);
}

PyObject* registerHookHandler(PyObject* self, PyObject* args)
{
    PyObject* hookType = PySequence_GetItem(args, 0);
    if(!hookType) {
        UK_LOG_ERROR("Invalid hookType for handler");
        return nullptr;
    }

    PyObject* callback = PySequence_GetItem(args, 1);
    if(!callback) {
        UK_LOG_ERROR("Invalid callback for handler");
        return nullptr;
    }
    ::Unknown::registerHook([=]() {
        if(!PyObject_CallObject(callback, NULL)) {
            UK_LOG_ERROR("Unable to call func");
            PyObject_Print(callback, stdout, Py_PRINT_RAW);
            PyErr_PrintEx(1);
        }
    }, (Unknown::HookType)PyLong_AsLong(hookType));
    Py_RETURN_NONE;
}

void Unknown::Python::Interpreter::loadScript(std::string name)
{
    //register a test method
    registerMethod("Unknown", "register_hook", "Add a base hook", registerHookHandler);


    log(UK_LOG_LEVEL_INFO, concat("Loading script", name));

    PyObject* testModule = PyImport_ImportModule(name.c_str());
    checkError(testModule);
    PyObject* initFunction = PyObject_GetAttrString(testModule, "init");
    if(initFunction)
    {
        PyObject_CallObject(initFunction, NULL);
    }
}