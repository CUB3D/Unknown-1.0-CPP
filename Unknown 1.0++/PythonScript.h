#ifndef PYTHONSCRIPT_H
#define PYTHONSCRIPT_H

#include "stdafx.h"
#include "Python.h"
#include <string>

namespace Unknown
{
    namespace Python
    {
        class Interperator()
        {
        public:
            PyObject* moduleSys;

            void init();
        }

        class Script()
        {
        public:
            void checkError(PyObject* obj);
        
            void importModule(std::string name);

        }
    }
}

#endif
