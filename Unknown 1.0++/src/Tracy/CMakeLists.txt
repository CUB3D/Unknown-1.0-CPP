project(TRACY)

set(TRACY_SRC ${UK_CORE}/libs/third_party/Tracy/tracy/TracyClient.cpp)

add_library(TRACY SHARED ${TRACY_SRC})
target_include_directories(TRACY PUBLIC ${UK_CORE}/libs/third_party/Tracy/tracy)