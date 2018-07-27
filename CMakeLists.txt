cmake_minimum_required(VERSION 3.9)
set(CMAKE_CXX_STANDARD 17)

project("Unknown development tool")

set(UK_DIR ${PROJECT_SOURCE_DIR})
message("UK_DIR: ${UK_DIR}")

set(UK_INCLUDE "${UK_DIR}/Unknown 1.0++")

if(UNIX)
	set(UK_LIB "${UK_DIR}/Output/lib/linux/")
endif()

if(WIN32)
	set(UK_LIB "${UK_DIR}/Output/lib/nt")
endif()

set(RJ_INCLUDE ${UK_DIR}/Libs/RapidJSON/include/rapidjson)

set(CMAKE_MODULE_PATH ${UK_DIR}/tools/build/cmake-scripts)

if(UNIX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -ggdb")
endif()

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

# Find python
find_package(PythonLibs)
if(PYTHONLIBS_FOUND)
    message("Python found: ${PYTHON_INCLUDE_DIRS}:${PYTHON_LIBRARIES}")
endif()

# Find box2d
find_package(Box2D REQUIRED)
if(BOX2D_FOUND)
    message("Found box2d: ${BOX2D_INCLUDE_DIR}:${BOX2D_LIBRARY}")
endif()

# TODO: This is a mega hack
link_directories(${UK_LIB})

add_executable(devTool "DevLib/UnknownTest.cpp")


if(UNIX)
    set(UNIX_LIBS pthread dl util m stdc++fs)
endif()

if(WIN32)
    set(WIN32_LIBS ${SDL2MAIN_LIBRARY})
endif()



SET(COMBINED_LIBS ${SDL2_TTF_LIBRARY} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_MIXER_LIBRARY} ${PYTHON_LIBRARY} ${BOX2D_LIBRARY} ${UNIX_LIBS} ${WIN32_LIBS})
SET(COMBINED_INCLUDE ${RJ_INCLUDE} ${PYTHON_INCLUDE_DIRS} ${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIR} ${BOX2D_INCLUDE_DIR})


FILE(GLOB_RECURSE UK_ENGINE_SRC "Unknown 1.0++/*.cpp")
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
add_custom_command(TARGET UK POST_BUILD COMMAND python ${PROJECT_SOURCE_DIR}/tools/build/exportHeaders.py ${PROJECT_SOURCE_DIR})

FILE(GLOB_RECURSE UK_TEST_SRC "Unknown Test/*.cpp")
add_executable(UKTest ${UK_TEST_SRC})
target_include_directories(UKTest PUBLIC ${UK_INCLUDE} ${COMBINED_INCLUDE})
target_link_libraries(UKTest UK ${COMBINED_LIBS})
