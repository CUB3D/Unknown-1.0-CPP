#ifndef PYTHONSCRIPT_H
#define PYTHONSCRIPT_H

#include "stdafx.h"
#include "Python.h"
#include <string>

namespace Unknown
{
    namespace Python
    {
        class Interpreter
        {
        public:
            PyObject* moduleSys;
            
            void checkError(PyObject* obj);
            void addSearchPath(std::string name);
            void init();
        };

        extern Interpreter* instance;

        Interpreter* getInterpreter();
    }
}

#endif
