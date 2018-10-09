# Created by cub3d, part of Unknown 3.0

if(WIN32)
    find_package(PythonLibs)
elseif(UNIX)
	FIND_LIBRARY(PYTHON_LIBRARIES
        NAMES python3.8 python3.7 python3.6
        HINTS
        PATH_SUFFIXES
        PATHS
		/usr
        NO_DEFAULT_PATH
        )

	FIND_PATH(PYTHON_INCLUDE_DIRS
		NAMES Python.h
		PATH_SUFFIXES python3.8m python3.7m python3.6m
		PATHS
		/usr/include
		)
endif()

INCLUDE(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(UKPython REQUIRED_VARS PYTHON_LIBRARIES PYTHON_INCLUDE_DIRS)

