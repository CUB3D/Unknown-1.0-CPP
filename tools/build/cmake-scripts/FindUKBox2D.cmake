# Use the standard find on windows
if(WIN32)
	#find_package(Box2DWin REQUIRED)
	FIND_LIBRARY(BOX2D_LIBRARY
        NAMES Box2D
        PATH_SUFFIXES Release
        PATHS
        ${UK_DIR}/Libs/Box2D/Box2D/Build/vs2017/bin
        NO_DEFAULT_PATH
        )

    find_path(BOX2D_INCLUDE_DIR
            Box2D/Box2D.h
            PATH_SUFFIXES Box2D
            PATHS
            ${UK_DIR}/Libs/Box2D/Box2D
            NO_DEFAULT_PATH
            )


elseif(CMAKE_CXX_COMPILER MATCHES "/em\\+\\+(-[a-zA-Z0-9.])?$") # Emscripten
    # Look for manually cross compiled libs
    FIND_LIBRARY(BOX2D_LIBRARY
            NAMES Box2D
            PATH_SUFFIXES Debug
            PATHS
            /usr
            ${UK_DIR}/Libs/Box2D/Box2D/Build/gmake2/bin
            NO_DEFAULT_PATH
            )

    find_path(BOX2D_INCLUDE_DIR
            Box2D/Box2D.h
            PATH_SUFFIXES Box2D
            PATHS
            ${UK_DIR}/Libs/Box2D/Box2D
            NO_DEFAULT_PATH
            )
elseif(UNIX)
    FIND_LIBRARY(BOX2D_LIBRARY
            NAMES Box2D
            PATH_SUFFIXES lib/x86_64-linux-gnu lib
            PATHS
            /usr
            NO_DEFAULT_PATH
            )

    find_path(BOX2D_INCLUDE_DIR
            Box2D/Box2D.h
            PATH_SUFFIXES include
            PATHS
            /usr
            NO_DEFAULT_PATH
            )
endif()

if(BOX2D_INCLUDE_DIR)
    if(BOX2D_LIBRARY)
        set(BOX2D_FOUND TRUE)
    endif(BOX2D_LIBRARY)
endif(BOX2D_INCLUDE_DIR)

INCLUDE(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(UKBox2D REQUIRED_VARS BOX2D_LIBRARY BOX2D_INCLUDE_DIR)
