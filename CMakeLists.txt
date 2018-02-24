cmake_minimum_required(VERSION 3.9)
set(CMAKE_CXX_STANDARD 17)

project("Unknown development tool")

set(UK_DIR ${PROJECT_SOURCE_DIR})
message("UK_DIR: ${UK_DIR}")

set(UK_INCLUDE ${UK_DIR}/Output/lib/linux/include)
set(UK_LIB ${UK_DIR}/Output/lib/linux)
set(RJ_INCLUDE ${UK_DIR}/Libs/RapidJSON/include/rapidjson)

set(CMAKE_MODULE_PATH ${UK_DIR}/tools/build/cmake-scripts)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -ggdb")

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

# Find python
find_package(PythonLibs)
if(PYTHONLIBS_FOUND)
    message("Python found: ${PYTHON_INCLUDE_DIRS}:${PYTHON_LIBRARIES}")
endif()

# TODO: This is a mega hack
link_directories(${UK_LIB})

add_executable(devTool "DevLib/UnknownTest.cpp")

FILE(GLOB_RECURSE UK_ENGINE_SRC "Unknown 1.0++/*.cpp")
add_library(UK SHARED ${UK_ENGINE_SRC})
target_include_directories(UK PUBLIC ${RJ_INCLUDE} ${PYTHON_INCLUDE_DIRS} ${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR})
target_link_libraries(UK ${SDL2_TTF_LIBRARIES} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${PYTHON_LIBRARIES} pthread dl util m)
set_target_properties(UK PROPERTIES CMAKE_LIBRARY_OUTPUT_DIRECTORY ${UK_LIB})
add_custom_command(TARGET UK POST_BUILD COMMAND "${PROJECT_SOURCE_DIR}/tools/build/exportHeaders.py")

FILE(GLOB_RECURSE UK_TEST_SRC "Unknown Test/*.cpp")
add_executable(UKTest ${UK_TEST_SRC})
target_include_directories(UKTest PUBLIC ${UK_INCLUDE} ${RJ_INCLUDE} ${PYTHON_INCLUDE_DIRS} ${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR})
target_link_libraries(UKTest UK ${SDL2_TTF_LIBRARY} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${PYTHON_LIBRARIES} pthread dl util m)