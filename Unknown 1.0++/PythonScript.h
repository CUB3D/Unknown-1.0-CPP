#ifndef PYTHONSCRIPT_H
#define PYTHONSCRIPT_H

#include "stdafx.h"
#include <Python.h>
#include <string>
#include <memory>
#include <functional>

namespace Unknown
{
    namespace Python
    {
        // Get the python type for a c++ type
        template<typename T>
        PyObject* getPyType(T a) {
            if(typeid(a) == typeid(bool)) {
                return a ? Py_True : Py_False;
            }

            return Py_None;
        }


        class Interpreter;
        extern std::shared_ptr<Interpreter> instance;

        std::shared_ptr<Interpreter> getInterpreter();


        class Interpreter
        {
        public:
            PyObject* moduleSys;

            void checkError(PyObject* obj);
            void addSearchPath(std::string name);
            void loadScript(std::string name);
            void init();

            PyObject* getMethod(const std::string& method);
            void callMethod(const std::string& method, PyObject* argsTuple);
        };


        //TODO: find a good place for this
        // Take a variable number of variable typed args and the current recursion level as well as the tuple to store in
        auto tmp = [](PyObject* t, int x, auto&& a, auto&&... b) {
            // Get the python type of the current variable
            PyObject* result = ::Unknown::Python::getPyType(a);
            // Store it in the tuple
            PyTuple_SetItem(t, x, result);
            // If not on the last element, recursively call self, this will take the next value out of the param pack and deduce its type for auto
            if constexpr (sizeof...(b) > 0) {
                tmp(t, x, b...);
            }
        };

        auto pythonFunc = [](const std::string& name) {
            return [name](auto... args) {
                auto size = sizeof...(args);
                PyObject *tuple = PyTuple_New(size);
                tmp(tuple, 0, args...);
                ::Unknown::Python::getInterpreter()->callMethod(name, tuple);
            };
        };
    }
}

#define UK_PYTHON_ADD_SEARCH_PATH(path) ::Unknown::Python::getInterpreter()->addSearchPath(path)
#define UK_PYTHON_LOAD_SCRIPT(name) ::Unknown::Python::getInterpreter()->loadScript(name)
#define UK_PYTHON_FUNC(name) ::Unknown::Python::pythonFunc(name)

#endif
