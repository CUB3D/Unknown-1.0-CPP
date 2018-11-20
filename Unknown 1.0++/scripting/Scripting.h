//
// Created by cub3d on 18/11/18.
//

#ifndef UNKNOWN_SCRIPTING_H
#define UNKNOWN_SCRIPTING_H

// Only include python if support is being built
#ifdef PYTHON_SCRIPT_ENABLED
#include <scripting/python/PythonScript.h>
#endif

#include <scripting/lua/LuaScript.h>

#include <scripting/SharedVariable.h>

#endif //UNKNOWN_SCRIPTING_H
