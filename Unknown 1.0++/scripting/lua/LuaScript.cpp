//
// Created by cub3d on 18/11/18.
//

#include "LuaScript.h"

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
};

void LuaScript::test() {
    constexpr static const char* script = "print 'Hi from lua'";


    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    luaL_dostring(L, script);
    lua_close(L);
}