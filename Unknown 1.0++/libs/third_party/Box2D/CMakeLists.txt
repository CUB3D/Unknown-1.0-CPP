FILE(GLOB_RECURSE BOX2D_SRC "${THIRD_PARTY}/Box2D/Box2D/Box2D/*.c*")

add_library(Box2D STATIC ${BOX2D_SRC})
target_include_directories(Box2D PUBLIC ${THIRD_PARTY}/Box2D/Box2D)