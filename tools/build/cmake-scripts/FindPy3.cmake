# Created by cub3d, part of Unknown 3.0


# Find the libpython.so
FILE(GLOB PYTHON_LIBRARIES /usr/lib/libpython3.*m.so)

# Find the path to the headers
FILE(GLOB PY3_INCLUDE_DIR_BASE /usr/include/python3.*m/)

FIND_PATH(PYTHON_INCLUDE_DIRS Python.h
	HINTS
		${PY3_INCLUDE_DIR_BASE}
)

INCLUDE(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(Py3 REQUIRED_VARS PYTHON_LIBRARIES PYTHON_INCLUDE_DIRS)

