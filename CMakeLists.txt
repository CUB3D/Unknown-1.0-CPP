cmake_minimum_required(VERSION 3.9)
set(CMAKE_CXX_STANDARD 17)

project("Unknown development tool")

set(UK_DIR ${PROJECT_SOURCE_DIR})
set(UK_PROJECT_NAME UKTest)


set(UK_INCLUDE "${UK_DIR}/Unknown 1.0++")
set(UK_LIB "${UK_DIR}/Output/lib/${CMAKE_HOST_SYSTEM_NAME}/")
set(CMAKE_MODULE_PATH "${UK_DIR}/tools/build/cmake-scripts")

# Enable debugging on g++
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -ggdb -pg -O3")
endif()

# Emscripten support
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(UK_PROJECT_NAME ${UK_PROJECT_NAME}.html)

    # TODO: add simd when it is supported with wasm
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -isystem -s USE_SDL=2 -s USE_SDL_TTF=2 -s USE_SDL_IMAGE=2 -s USE_LIBPNG=1 -s USE_WEBGL2=1 -s WASM=1 -s DEMANGLE_SUPPORT=1 -s FULL_ES2=1 -s FULL_ES3=1 NO_EXIT_RUNTIME=0 -s SDL2_IMAGE_FORMATS='[\"png\"]' --preload-file '/home/cub3d/Development/git/Unknown-1.0-CPP/Unknown Test/Player.png@Player.png' --preload-file '/home/cub3d/Development/git/Unknown-1.0-CPP/Unknown Test/ImageVert.glsl@ImageVert.glsl' --preload-file '/home/cub3d/Development/git/Unknown-1.0-CPP/Unknown Test/ImageFrag.glsl@ImageFrag.glsl'")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --preload-file '/home/cub3d/Development/git/Unknown-1.0-CPP/Unknown Test/Ground.json@Ground.json'")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --preload-file '/home/cub3d/Development/git/Unknown-1.0-CPP/Unknown Test/Obstacle.json@Obstacle.json'")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --preload-file '/home/cub3d/Development/git/Unknown-1.0-CPP/Unknown Test/PlayerEntity.json@PlayerEntity.json'")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --preload-file '/home/cub3d/Development/git/Unknown-1.0-CPP/Unknown Test/OtherPlayerEntity.json@OtherPlayerEntity.json'")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --preload-file '/home/cub3d/Development/git/Unknown-1.0-CPP/Unknown Test/Bullet.json@Bullet.json'")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --preload-file '/home/cub3d/Development/git/Unknown-1.0-CPP/Unknown Test/OtherBullet.json@OtherBullet.json'")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --preload-file '/home/cub3d/Development/git/Unknown-1.0-CPP/Unknown Test/PhysGameGUI.json@PhysGameGUI.json'")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --preload-file '/home/cub3d/Development/git/Unknown-1.0-CPP/Unknown Test/Fonts/Arimo-Regular.ttf@Fonts/Arimo-Regular.ttf'")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --preload-file '/home/cub3d/Development/git/Unknown-1.0-CPP/Unknown Test/Fonts/Arimo-Regular.ttf@Fonts/Arimo-Regular.ttf'")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --preload-file '/home/cub3d/Development/git/Unknown-1.0-CPP/Unknown Test/Hit.wav@Hit.wav'")
endif()


# Find rapidjson
set(RJ_INCLUDE ${UK_DIR}/Libs/RapidJson/include/rapidjson)

# Find SDL2
find_package(SDL2 REQUIRED)
if(SDL2_FOUND)
    message("SDL2 Found: ${SDL2_INCLUDE_DIR}:${SDL2_LIBRARY}")
endif()

# Find SDL2_image
find_package(SDL2_image REQUIRED)
if(SDL2_IMAGE_FOUND)
    message("SDL2_image Found: ${SDL2_IMAGE_INCLUDE_DIR}:${SDL2_IMAGE_LIBRARY}")
endif()

# Find SDL2_ttf
find_package(SDL2_ttf REQUIRED)
if(SDL2_TTF_FOUND)
    message("SDL2_ttf Found: ${SDL2_TTF_INCLUDE_DIR}:${SDL2_TTF_LIBRARY}")
endif()

# Find SDL2_mixer
find_package(SDL2_mixer REQUIRED)
if(SDL_MXIXER_FOUND)
    message("SDL2_mixer: ${SDL2_MIXER_INCLUDE_DIR}:${SDL2_MIXER_LIBRARY}")
endif()

# Find Reflex
set(Reflex_INCLUDE ${UK_DIR}/Libs/Reflex)

# Find python
if(WIN32)
    set(PYTHON_INCLUDE_DIRS B:\\Programs\\python3.6.6\\include)
    set(PYTHON_LIBRARIES B:\\Programs\\python3.6.6\\libs\\python36.lib)
endif()

#TODO: Make work on windows and add REQUIRED

#find_package(Python3 COMPONENTS Development)
#if(Python3_FOUND)
#    message("Python found: ${Python3_INCLUDE_DIRS}:${Python3_LIBRARIES}")
#endif()

#TODO: Add this back in when cmake 3.12 is available

if(UNIX)
    find_package(PythonLibs)
    if(PYTHONLIBS_FOUND)
        message("Python found: ${PYTHON_INCLUDE_DIRS}:${PYTHON_LIBRARIES}")
    endif(PYTHONLIBS_FOUND)
endif(UNIX)

# Find box2d
find_package(UKBox2D)
if(BOX2D_FOUND)
    message("Found box2d: ${BOX2D_INCLUDE_DIR}:${BOX2D_LIBRARY}")
endif()


find_package(UKAssimp)

#set(ASSIMP_LIBRARY_DIRS /usr/lib/libassimp.so)
#
#if(TRAVIS)
#    set(ASSIMP_LIBRARY_DIRS /usr/lib/x86_64-linux-gnu/libassimp.so)
#endif(TRAVIS)
#
#if(WIN32)
#	set(ASSIMP_INCLUDE_DIRS ${UK_DIR}/Libs/assimp/include)
#	set(ASSIMP_LIBRARY_DIRS ${UK_DIR}/Libs/assimp/lib/Debug/assimp-vc140-mt.lib)
#endif()

if(ASSIMP_FOUND)
    message("Found assimp ${ASSIMP_INCLUDE_DIRS}:${ASSIMP_LIBRARY_DIRS}")
endif()

# Find glm
set(GLM_INCLUDE_DIR ${UK_DIR}/Libs/glm/)


# TODO: This is a mega hack
link_directories(${UK_LIB})

if(UNIX)
    set(UNIX_LIBS pthread dl util m stdc++fs)
endif()


SET(COMBINED_LIBS ${SDL2_TTF_LIBRARY} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_MIXER_LIBRARY} ${PYTHON_LIBRARIES} ${BOX2D_LIBRARY} ${UNIX_LIBS} ${SDL2MAIN_LIBRARY} ${ASSIMP_LIBRARY_DIRS})
SET(COMBINED_INCLUDE ${RJ_INCLUDE} ${PYTHON_INCLUDE_DIRS} ${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIR} ${BOX2D_INCLUDE_DIR} ${Reflex_INCLUDE} ${GLM_INCLUDE_DIR} ${ASSIMP_INCLUDE_DIRS})

message("LIBS: ${COMBINED_LIBS}")
message("INCLUDE: ${COMBINED_INCLUDE}")

FILE(GLOB_RECURSE UK_ENGINE_SRC "Unknown 1.0++/*.c*")
if(WIN32)
	add_library(UK STATIC ${UK_ENGINE_SRC})
endif()
if(UNIX)
	add_library(UK SHARED ${UK_ENGINE_SRC})
endif()

target_include_directories(UK PUBLIC ${COMBINED_INCLUDE})
target_link_libraries(UK ${COMBINED_LIBS})
set_target_properties(UK PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${UK_LIB})
set_target_properties(UK PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${UK_LIB})
set_target_properties(UK PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${UK_LIB})
add_custom_command(TARGET UK POST_BUILD COMMAND python ${PROJECT_SOURCE_DIR}/tools/build/exportHeaders.py ${PROJECT_SOURCE_DIR} ${CMAKE_HOST_SYSTEM_NAME})

FILE(GLOB_RECURSE UK_TEST_SRC "Unknown Test/*.cpp")

add_executable(${UK_PROJECT_NAME} ${UK_TEST_SRC})
target_include_directories(${UK_PROJECT_NAME} PUBLIC ${UK_INCLUDE} ${COMBINED_INCLUDE})
target_link_libraries(${UK_PROJECT_NAME} UK ${COMBINED_LIBS})
