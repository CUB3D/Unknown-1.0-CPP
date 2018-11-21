add_subdirectory(liblua)

add_library(LUASCRIPT LuaScript.cpp)
target_link_libraries(LUASCRIPT LUA)