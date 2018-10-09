# Use the standard find on windows
if(WIN32)
	#find_package(Box2DWin REQUIRED)
elseif(CMAKE_CXX_COMPILER MATCHES "/em\\+\\+(-[a-zA-Z0-9.])?$") # Emscripten
    # Look for manually cross compiled libs
    FIND_LIBRARY(ASSIMP_LIBRARY_DIRS
            NAMES assimp
            HINTS
            PATH_SUFFIXES code
            PATHS
            ${UK_DIR}/Libs/assimp/build
            NO_DEFAULT_PATH
            )

    find_path(ASSIMP_INCLUDE_DIRS
            NAMES assimp/scene.h
            PATH_SUFFIXES include
            PATHS
            ${UK_DIR}/Libs/assimp
            NO_DEFAULT_PATH
            )

    # Some of the headers are generated at build time, such as
    # config.h
    find_path(ASSIMP_GENERATED_INCLUDES
            NAMES assimp/config.h
            PATH_SUFFIXES include
            PATHS
            ${UK_DIR}/Libs/assimp/build
            NO_DEFAULT_PATH
            )

    # Append generated and standard includes
    set(ASSIMP_INCLUDE_DIRS "${ASSIMP_INCLUDE_DIRS};${ASSIMP_GENERATED_INCLUDES}")
elseif(UNIX)
    find_package(assimp)
endif()

if(ASSIMP_INCLUDE_DIRS)
    if(ASSIMP_LIBRARY_DIRS)
        set(ASSIMP_FOUND TRUE)
    endif(ASSIMP_LIBRARY_DIRS)
endif(ASSIMP_INCLUDE_DIRS)

INCLUDE(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(UKAssimp REQUIRED_VARS ASSIMP_LIBRARY_DIRS ASSIMP_INCLUDE_DIRS)
