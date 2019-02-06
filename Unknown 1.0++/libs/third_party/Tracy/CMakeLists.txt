project(TRACY)

set(TRACY_SRC
        tracy/TracyClient.cpp
        tracy/common/tracy_lz4.cpp
        tracy/client/TracyProfiler.cpp
        tracy/client/TracyCallstack.cpp
        tracy/common/TracySocket.cpp
        tracy/client/tracy_rpmalloc.cpp
        )

set(UK_ENGINE_SRC ${UK_ENGINE_SRC} ${UK_CORE}/libs/third_party/Tracy/tracy/TracyClient.cpp)
#set(COMBINED_INCLUDE ${COMBINED_INCLUDE} ${UK_CORE}/libs/third_party/Tracy/tracy)
set(COMBINED_LIBS ${COMBINED_LIBS} TRACY)

add_library(TRACY SHARED ${TRACY_SRC})
target_include_directories(TRACY PUBLIC ${UK_CORE}/libs/third_party/Tracy/tracy)