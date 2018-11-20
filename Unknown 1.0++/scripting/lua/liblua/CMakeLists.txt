project(LUA C)

set(LUA_CORE_SRC
        "${UK_DIR}/Libs/lua/lua.c"
        "${UK_DIR}/Libs/lua/lopcodes.c"
        "${UK_DIR}/Libs/lua/lapi.c"
        "${UK_DIR}/Libs/lua/lcode.c"
        "${UK_DIR}/Libs/lua/lctype.c"
        "${UK_DIR}/Libs/lua/ldebug.c"
        "${UK_DIR}/Libs/lua/ldo.c"
        "${UK_DIR}/Libs/lua/ldump.c"
        "${UK_DIR}/Libs/lua/lfunc.c"
        "${UK_DIR}/Libs/lua/lgc.c"
        "${UK_DIR}/Libs/lua/llex.c"
        "${UK_DIR}/Libs/lua/lmem.c"
        "${UK_DIR}/Libs/lua/lobject.c"
        "${UK_DIR}/Libs/lua/lparser.c"
        "${UK_DIR}/Libs/lua/lstate.c"
        "${UK_DIR}/Libs/lua/lstring.c"
        "${UK_DIR}/Libs/lua/ltable.c"
        "${UK_DIR}/Libs/lua/ltm.c"
        "${UK_DIR}/Libs/lua/lundump.c"
        "${UK_DIR}/Libs/lua/lvm.c"
        "${UK_DIR}/Libs/lua/lzio.c"
        "${UK_DIR}/Libs/lua/ltests.c"

        )

set(LUA_AUX_SRC "${UK_DIR}/Libs/lua/lauxlib.c")

set(LUA_LIB_SRC
        "${UK_DIR}/Libs/lua/lbaselib.c"
        "${UK_DIR}/Libs/lua/ldblib.c"
        "${UK_DIR}/Libs/lua/liolib.c"
        "${UK_DIR}/Libs/lua/lmathlib.c"
        "${UK_DIR}/Libs/lua/loslib.c"
        "${UK_DIR}/Libs/lua/ltablib.c"
        "${UK_DIR}/Libs/lua/lstrlib.c"
        "${UK_DIR}/Libs/lua/lutf8lib.c"
        "${UK_DIR}/Libs/lua/loadlib.c"
        "${UK_DIR}/Libs/lua/lcorolib.c"
        "${UK_DIR}/Libs/lua/linit.c")

set(LUA_SRC ${LUA_CORE_SRC} ${LUA_AUX_SRC} ${LUA_LIB_SRC})

message("LUA_SRC ${LUA_SRC}")

add_library(LUA STATIC ${LUA_SRC})
target_include_directories(LUA PUBLIC "${UK_DIR}/Libs/lua")