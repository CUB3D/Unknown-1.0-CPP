set(PYTHON_SCRIPT_SRC
        PythonScript.cpp)

# Find python
find_package(UKPython)
if(PYTHONLIBS_FOUND)
    message("Python found: ${PYTHON_INCLUDE_DIRS}:${PYTHON_LIBRARIES}")
endif(PYTHONLIBS_FOUND)

add_definitions(-DPYTHON_SCRIPT_ENABLED)

add_library(PYTHONSCRIPT STATIC ${PYTHON_SCRIPT_SRC})
target_link_libraries(PYTHONSCRIPT ${PYTHON_LIBRARIES})
target_include_directories(PYTHONSCRIPT PUBLIC ${PYTHON_INCLUDE_DIRS})