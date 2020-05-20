project(LUA C)

set(LUA_CORE_SRC
        "${UK_DIR}/Engine/libs/third_party/lua/lua/lua.c"
        "${UK_DIR}/Engine/libs/third_party/lua/lua/lopcodes.c"
        "${UK_DIR}/Engine/libs/third_party/lua/lua/lapi.c"
        "${UK_DIR}/Engine/libs/third_party/lua/lua/lcode.c"
        "${UK_DIR}/Engine/libs/third_party/lua/lua/lctype.c"
        "${UK_DIR}/Engine/libs/third_party/lua/lua/ldebug.c"
        "${UK_DIR}/Engine/libs/third_party/lua/lua/ldo.c"
        "${UK_DIR}/Engine/libs/third_party/lua/lua/ldump.c"
        "${UK_DIR}/Engine/libs/third_party/lua/lua/lfunc.c"
        "${UK_DIR}/Engine/libs/third_party/lua/lua/lgc.c"
        "${UK_DIR}/Engine/libs/third_party/lua/lua/llex.c"
        "${UK_DIR}/Engine/libs/third_party/lua/lua/lmem.c"
        "${UK_DIR}/Engine/libs/third_party/lua/lua/lobject.c"
        "${UK_DIR}/Engine/libs/third_party/lua/lua/lparser.c"
        "${UK_DIR}/Engine/libs/third_party/lua/lua/lstate.c"
        "${UK_DIR}/Engine/libs/third_party/lua/lua/lstring.c"
        "${UK_DIR}/Engine/libs/third_party/lua/lua/ltable.c"
        "${UK_DIR}/Engine/libs/third_party/lua/lua/ltm.c"
        "${UK_DIR}/Engine/libs/third_party/lua/lua/lundump.c"
        "${UK_DIR}/Engine/libs/third_party/lua/lua/lvm.c"
        "${UK_DIR}/Engine/libs/third_party/lua/lua/lzio.c"
        "${UK_DIR}/Engine/libs/third_party/lua/lua/ltests.c"

        )

set(LUA_AUX_SRC "${UK_DIR}/Engine/libs/third_party/lua/lua/lauxlib.c")

set(LUA_LIB_SRC
        "${UK_DIR}/Engine/libs/third_party/lua/lua/lbaselib.c"
        "${UK_DIR}/Engine/libs/third_party/lua/lua/ldblib.c"
        "${UK_DIR}/Engine/libs/third_party/lua/lua/liolib.c"
        "${UK_DIR}/Engine/libs/third_party/lua/lua/lmathlib.c"
        "${UK_DIR}/Engine/libs/third_party/lua/lua/loslib.c"
        "${UK_DIR}/Engine/libs/third_party/lua/lua/ltablib.c"
        "${UK_DIR}/Engine/libs/third_party/lua/lua/lstrlib.c"
        "${UK_DIR}/Engine/libs/third_party/lua/lua/lutf8lib.c"
        "${UK_DIR}/Engine/libs/third_party/lua/lua/loadlib.c"
        "${UK_DIR}/Engine/libs/third_party/lua/lua/lcorolib.c"
        "${UK_DIR}/Engine/libs/third_party/lua/lua/linit.c")

set(LUA_SRC ${LUA_CORE_SRC} ${LUA_AUX_SRC} ${LUA_LIB_SRC})

message("LUA_SRC ${LUA_SRC}")

add_library(LUA STATIC ${LUA_SRC})
target_include_directories(LUA PUBLIC "${UK_DIR}/Engine/libs/third_party/lua/lua")