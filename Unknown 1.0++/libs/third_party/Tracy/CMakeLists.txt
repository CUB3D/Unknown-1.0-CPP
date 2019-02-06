project(TRACY)

set(TRACY_SRC tracy/TracyClient.cpp)

set(COMBINED_INCLUDE ${COMBINED_INCLUDE} tracy)

add_library(TRACY SHARED ${TRACY_SRC})
target_include_directories(TRACY PUBLIC tracy)