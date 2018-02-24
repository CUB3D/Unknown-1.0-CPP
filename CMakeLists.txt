cmake_minimum_required(VERSION 3.9)

set(CMAKE_CXX_STANDARD 17)

project("Unknown development tool")

include_directories(Output/lib/linux/include Libs/RapidJSON/include/rapidjson /usr/include/python3.6m /usr/include/SDL2)
link_directories(Output/lib/linux)
link_libraries(libUK.so)

add_executable(devTool "DevLib/UnknownTest.cpp")

FILE(GLOB_RECURSE UK_ENGINE_SRC "Unknown 1.0++/*.cpp")
add_library(UK SHARED ${UK_ENGINE_SRC})
set_target_properties(UK PROPERTIES CMAKE_LIBRARY_OUTPUT_DIRECTORY Output/lib/linux)
add_custom_command(TARGET UK POST_BUILD COMMAND "${PROJECT_SOURCE_DIR}/tools/build/exportHeaders.py")

FILE(GLOB_RECURSE UK_TEST_SRC "Unknown Test/*.cpp")
add_executable(UKTest ${UK_TEST_SRC})
target_link_libraries(UKTest UK SDL2_ttf SDL2 SDL2main SDL2_image python3.6m pthread dl util m -ggdb)