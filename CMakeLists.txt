cmake_minimum_required(VERSION 3.9)

set(UK_DIR ${CMAKE_CURRENT_SOURCE_DIR})


set(UK_LIB "${UK_DIR}/Output/lib/${CMAKE_HOST_SYSTEM_NAME}/")
set(CMAKE_MODULE_PATH "${UK_DIR}/tools/build/cmake-scripts")

# Enable debugging on g++
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -ggdb -pg")
endif()

if(UNIX)
	set(UNIX_LIBS pthread dl util m stdc++fs)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
endif(UNIX)

if(WIN32)
    # Avoid __dllexport, etc
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MD /Zi")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /MD /Zi")
endif(WIN32)

# Emscripten support
if(CMAKE_CXX_COMPILER MATCHES "/em\\+\\+(-[a-zA-Z0-9.])?$") # Emscripten
    set(CMAKE_CXX_COMPILE_FEATURES "cxx_template_template_parameters;cxx_alias_templates;cxx_alignas;cxx_alignof;cxx_attributes;cxx_auto_type;cxx_constexpr;cxx_decltype;cxx_decltype_incomplete_return_types;cxx_default_function_template_args;cxx_defaulted_functions;cxx_defaulted_move_initializers;cxx_delegating_constructors;cxx_deleted_functions;cxx_enum_forward_declarations;cxx_explicit_conversions;cxx_extended_friend_declarations;cxx_extern_templates;cxx_final;cxx_func_identifier;cxx_generalized_initializers;cxx_inheriting_constructors;cxx_inline_namespaces;cxx_lambdas;cxx_local_type_template_args;cxx_long_long_type;cxx_noexcept;cxx_nonstatic_member_init;cxx_nullptr;cxx_override;cxx_range_for;cxx_raw_string_literals;cxx_reference_qualified_functions;cxx_right_angle_brackets;cxx_rvalue_references;cxx_sizeof_member;cxx_static_assert;cxx_strong_enums;cxx_thread_local;cxx_trailing_return_types;cxx_unicode_literals;cxx_uniform_initialization;cxx_unrestricted_unions;cxx_user_literals;cxx_variadic_macros;cxx_variadic_templates;cxx_aggregate_default_initializers;cxx_attribute_deprecated;cxx_binary_literals;cxx_contextual_conversions;cxx_decltype_auto;cxx_digit_separators;cxx_generic_lambdas;cxx_lambda_init_captures;cxx_relaxed_constexpr;cxx_return_type_deduction;cxx_variable_templates")

    # TODO: add simd when it is supported with wasm
        #-s DEMANGLE_SUPPORT=1

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -isystem -s USE_SDL=2 -s USE_SDL_TTF=2 -s USE_SDL_IMAGE=2 -s USE_LIBPNG=1 -s USE_WEBGL2=1 -s WASM=1 -s USE_ZLIB=1 -s NO_EXIT_RUNTIME=0 -s ALLOW_MEMORY_GROWTH=1 -s SDL2_IMAGE_FORMATS='[\"png\"]'")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --preload-file '/home/cub3d/Development/git/Unknown-1.0-CPP/Unknown Test/Player.png@Player.png'")
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

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --preload-file '/home/cub3d/Development/git/Unknown-1.0-CPP/Unknown Test/skybox@skybox'")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --preload-file '/home/cub3d/Development/git/Unknown-1.0-CPP/Unknown Test/teapot.obj@teapot.obj'")

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --preload-file '/home/cub3d/Development/git/Unknown-1.0-CPP/Unknown Test/Test.glsl@Test.glsl'")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --preload-file '/home/cub3d/Development/git/Unknown-1.0-CPP/Unknown Test/TestFrag.glsl@TestFrag.glsl'")

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --preload-file '/home/cub3d/Development/git/Unknown-1.0-CPP/Unknown Test/FBO_vert.glsl@FBO_vert.glsl'")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --preload-file '/home/cub3d/Development/git/Unknown-1.0-CPP/Unknown Test/FBO_Frag.glsl@FBO_Frag.glsl'")

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --preload-file '/home/cub3d/Development/git/Unknown-1.0-CPP/Unknown Test/Sky_vert.glsl@Sky_vert.glsl'")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --preload-file '/home/cub3d/Development/git/Unknown-1.0-CPP/Unknown Test/Sky_frag.glsl@Sky_frag.glsl'")

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --preload-file '/home/cub3d/Development/git/Unknown-1.0-CPP/Unknown Test/nano@nano'")
endif()

# Always build libs as static
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_BUILD_TYPE MinSizeRel)


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

# Find assimp
# Need to build zlib also
set(ASSIMP_BUILD_ZLIB ON CACHE BOOL "Enable to build zlib")
# No build tests
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "Enable to build tests")
# No need for tools
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "Enable to build additional tools")
# Don't add (d) to end of debug libs
set(INJECT_DEBUG_POSTFIX OFF CACHE BOOL "Enable to add postfix to debug libraries")
# Currently no need for exporting
set(ASSIMP_NO_EXPORT ON CACHE BOOL "Enable to build exporters")
# Currently this importer won't build with emscripten
set(ASSIMP_BUILD_GLTF_IMPORTER OFF CACHE BOOL "Enable to build GLTF importer (not currently working with emscripten)")
# Disable CPack, as well as others
set(ASSIMP_OPT_BUILD_PACKAGES OFF CACHE BOOL "Enable to build additional packages")
add_subdirectory(${UK_DIR}/Libs/assimp)
set(ASSIMP_LIBRARY_DIRS assimp)
set(ASSIMP_INCLUDE_DIRS ${UK_DIR}/Libs/assimp/include)


# Find glm
set(GLM_TEST_ENABLE OFF CACHE BOOL "Enable to build tests")
add_subdirectory(${UK_DIR}/Libs/glm)
set(GLM_LIBRARY_DIRS glm_static)
set(GLM_INCLUDE_DIR ${UK_DIR}/Libs/glm)

# Find rttr
set(BUILD_RTTR_DYNAMIC OFF CACHE BOOL "Build the dynamic/shared version of RTTR library" FORCE)
set(BUILD_UNIT_TESTS OFF CACHE BOOL "Build the unit tests of RTTR" FORCE)
set(BUILD_STATIC ON CACHE BOOL "Build RTTR as static library" FORCE)
set(BUILD_EXAMPLES OFF CACHE BOOL "Enable this to build the examples" FORCE)
set(BUILD_DOCUMENTATION OFF CACHE BOOL "Enable this to build the documentation")
set(BUILD_INSTALLER OFF CACHE BOOL "Enable this to build the installer")
set(BUILD_PACKAGE OFF CACHE BOOL "Enable this to build the installer")
#set(USE_PCH OFF CACHE BOOL "Use precompiled header files for compilation")
add_subdirectory(${UK_DIR}/Libs/rttr)
set(RTTR_INCLUDE_DIR ${UK_DIR}/Libs/rttr/src)

# Find libpak
set(PAK_BUILD_TEST OFF CACHE BOOL "Build tests" FORCE)
add_subdirectory(${UK_DIR}/Libs/libPAK)
set(PAK_INCLUDE_DIR ${UK_DIR}/Libs/libPAK/include)

# Find rapidjson
set(RJ_INCLUDE ${UK_DIR}/Libs/RapidJson/include/rapidjson)

set(TMXLITE_STATIC_LIB ON CACHE BOOL "Build static libs")
add_subdirectory(${UK_DIR}/Libs/tmxlite/tmxlite)
set(TMXLITE_INCLUDE ${UK_DIR}/Libs/tmxlite/tmxlite/include)

SET(COMBINED_LIBS ${SDL2_TTF_LIBRARY} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_MIXER_LIBRARY} ${UNIX_LIBS} ${SDL2MAIN_LIBRARY} ${ASSIMP_LIBRARY_DIRS} ${GLM_LIBRARY_DIRS} PAK rttr_core_lib tmxlite)
SET(COMBINED_INCLUDE ${RJ_INCLUDE} ${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIR} ${GLM_INCLUDE_DIR} ${ASSIMP_INCLUDE_DIRS} ${PAK_INCLUDE_DIR} ${RTTR_INCLUDE_DIR} ${TMXLITE_INCLUDE})

message("LIBS: ${COMBINED_LIBS}")
message("INCLUDE: ${COMBINED_INCLUDE}")

add_subdirectory("Unknown 1.0++")
add_subdirectory("Unknown Test")
