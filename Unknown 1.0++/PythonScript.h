#ifndef PYTHONSCRIPT_H
#define PYTHONSCRIPT_H

#include "stdafx.h"
#include "Python.h"

namespace Unknown
{
    namespace Python
    {
        void checkError(PyObject* obj);

        void init();
    }
}

#endif
