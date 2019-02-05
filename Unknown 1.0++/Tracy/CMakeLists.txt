project(TRACY)

set(TRACY_SRC ${UK_DIR}/Libs/tracy/TracyClient.cpp)

add_library(TRACY SHARED ${TRACY_SRC})
target_include_directories(TRACY PUBLIC ${UK_DIR}/Libs/tracy)