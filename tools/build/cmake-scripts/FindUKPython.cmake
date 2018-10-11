# Created by cub3d, part of Unknown 3.0

if(WIN32)
    find_package(PythonLibs)
elseif(UNIX)

	set(PYTHON_VERSIONS python3.8m
						python3.7m
						python3.6m
						python3.5m
						python3.4m)

	FIND_LIBRARY(PYTHON_LIBRARIES
        NAMES ${PYTHON_VERSIONS}
        PATH_SUFFIXES lib lib/x86_64-linux-gnu
        PATHS
		/usr
        NO_DEFAULT_PATH
        )

	FIND_PATH(PYTHON_INCLUDE_DIRS
		NAMES Python.h
		PATH_SUFFIXES ${PYTHON_VERSIONS}
		PATHS
		/usr/include
		)
endif()

INCLUDE(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(UKPython REQUIRED_VARS PYTHON_LIBRARIES PYTHON_INCLUDE_DIRS)

