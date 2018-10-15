# Created by cub3d, part of Unknown 3.0

if(WIN32)
	#TODO
elseif(UNIX)

	FIND_LIBRARY(PAK_LIBRARIES
        NAMES ${PYTHON_VERSIONS}
        PATH_SUFFIXES lib lib/x86_64-linux-gnu
        PATHS
		/usr
        NO_DEFAULT_PATH
        )

	FIND_PATH(PAK_INCLUDE_DIRS
		NAMES LibPAK.h
		PATH_SUFFIXES include
		PATHS
		${UK_DIR}/Libs/libPAK
		)
endif()

INCLUDE(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(UKPython REQUIRED_VARS PAK_LIBRARIES PAK_INCLUDE_DIRS)

