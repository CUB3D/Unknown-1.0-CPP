cmake_minimum_required(VERSION 3.3)
project(Unknown_1_0_CPP)

#SDL stuff
set(SDL2_Flags "")
#paths
set(SDL2_ROOT     "Libs/SDL2")
set(SDL2_Includes "${SDL2_ROOT}/include")
set(SDL2_LibDir   "${SDL2_ROOT}/lib/x86")

add_library(SDL2     STATIC IMPORTED)
add_library(SDL2main STATIC IMPORTED)
set_property(TARGET SDL2     PROPERTY IMPORTED_LOCATION "${SDL2_LibDir}/SDL2.lib")
set_property(TARGET SDL2main PROPERTY IMPORTED_LOCATION "${SDL2_LibDir}/SDL2main.lib")
# the libs to link against
set(SDL2_Libs mingw32 SDL2 SDL2main m dinput8 dxguid dxerr8 user32 gdi32 winmm imm32 ole32 oleaut32 shell32 version uuid)

#SDL image stuff
set(SDL2_IMAGE_ROOT     "Libs/SDL2_image")
set(SDL2_IMAGE_Includes "${SDL2_IMAGE_ROOT}/include")
set(SDL2_IMAGE_LibDir   "${SDL2_IMAGE_ROOT}/lib/x86")

add_library(SDL2_IMAGE   STATIC IMPORTED)
set_property(TARGET SDL2_IMAGE PROPERTY IMPORTED_LOCATION "${SDL2_IMAGE_LibDir}/SDL2_image.lib")
set(SDL2_IMAGE_Libs SDL2_IMAGE)

#rapidjson stuff
set(RapidJSON_ROOT     "Libs/RapidJSON")
set(RapidJSON_Includes "${RapidJSON_ROOT}/include")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 ${SDL2_Flags}")

set(SOURCE_FILES
    "Unknown 1.0++/Animation.cpp"
    "Unknown 1.0++/Animation.h"
    "Unknown 1.0++/Colour.cpp"
    "Unknown 1.0++/Colour.h"
    "Unknown 1.0++/Entity.cpp"
    "Unknown 1.0++/Entity.h"
    "Unknown 1.0++/Font.cpp"
    "Unknown 1.0++/Font.h"
    "Unknown 1.0++/Image.cpp"
    "Unknown 1.0++/Image.h"
    "Unknown 1.0++/Input.cpp"
    "Unknown 1.0++/Input.h"
    "Unknown 1.0++/Loader.cpp"
    "Unknown 1.0++/Loader.h"
    "Unknown 1.0++/Map.cpp"
    "Unknown 1.0++/Map.h"
    "Unknown 1.0++/Particle.cpp"
    "Unknown 1.0++/Particle.h"
    "Unknown 1.0++/Physics.cpp"
    "Unknown 1.0++/Physics.h"
    "Unknown 1.0++/Quadtree.cpp"
    "Unknown 1.0++/Quadtree.h"
    "Unknown 1.0++/Sprite.cpp"
    "Unknown 1.0++/Sprite.h"
    "Unknown 1.0++/stdafx.cpp"
    "Unknown 1.0++/stdafx.h"
    "Unknown 1.0++/targetver.h"
    "Unknown 1.0++/Timer.cpp"
    "Unknown 1.0++/Timer.h"
    "Unknown 1.0++/UI.cpp"
    "Unknown 1.0++/UI.h"
    "Unknown 1.0++/UI2D.cpp"
    "Unknown 1.0++/UI2D.h"
    "Unknown 1.0++/Unknown.cpp"
    "Unknown 1.0++/Unknown.h"
    "Unknown 1.0++/Utils.cpp"
    "Unknown 1.0++/Utils.h"
    "Unknown 1.0++/Vector.cpp"
    "Unknown 1.0++/Vector.h")

add_library(Unknown_1_0_CPP STATIC ${SOURCE_FILES})

add_custom_target(combined ALL COMMAND ${CMAKE_CXX_ARCHIVE_CREATE} libcombined.a $<TARGET_FILE:Unknown_1_0_CPP>)

#SDL2 includes
target_include_directories(Unknown_1_0_CPP SYSTEM PRIVATE ${SDL2_Includes} ${SDL2_IMAGE_Includes} ${RapidJSON_Includes})
# link against the SDL (and its dependencies)

target_link_libraries(Unknown_1_0_CPP ${SDL2_Libs} ${SDL2_IMAGE_Libs})

#Now for the test stuff

set(TEST_SOURCE_FILES
        "Unknown Test/Unknown Test.cpp"
        "Unknown Test/stdafx.cpp"
        "Unknown Test/stdafx.h"
        "Unknown Test/targetver.h")

add_executable(Unknown_1_0_CPP_TEST ${TEST_SOURCE_FILES})

target_include_directories(Unknown_1_0_CPP_TEST SYSTEM PRIVATE ${SDL2_Includes} ${SDL2_IMAGE_Includes} ${RapidJSON_Includes} "Unknown 1.0++")
target_link_libraries(Unknown_1_0_CPP_TEST ${SDL2_Libs} ${SDL2_IMAGE_Libs} "Output/Debug/libUnknown_1_0_CPP.a")
