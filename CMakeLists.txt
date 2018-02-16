cmake_minimum_required(VERSION 3.9)

set(CMAKE_CXX_STANDARD 11)

project("Unknown development tool")

include_directories(Output/lib/linux/include Libs/RapidJSON/include/rapidjson /usr/include/python3.6m /usr/include/SDL2)
link_directories(Output/lib/linux)
link_libraries(libUK.so)

add_executable(devTool "DevLib/UnknownTest.cpp")
