FILE(GLOB_RECURSE BOX2D_SRC "${UK_DIR}/Libs/Box2D/Box2D/*.c*")

add_library(Box2D STATIC ${BOX2D_SRC})
target_include_directories(Box2D PUBLIC ${UK_DIR}/Libs/Box2D)