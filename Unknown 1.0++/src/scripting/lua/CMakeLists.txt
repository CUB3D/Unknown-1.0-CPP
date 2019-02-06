add_subdirectory(liblua)

add_subdirectory(${UK_DIR}/Libs/LuaBridge/Source ./luabridge/)

add_library(LUASCRIPT LuaScript.cpp)
target_link_libraries(LUASCRIPT LUA LuaBridge rttr_core_lib)