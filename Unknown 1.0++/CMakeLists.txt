FILE(GLOB_RECURSE UK_ENGINE_SRC "*.c*" )

add_subdirectory(Box2D)
add_subdirectory(Imgui)

add_library(UK SHARED ${UK_ENGINE_SRC})
target_include_directories(UK PUBLIC ${COMBINED_INCLUDE} "${UK_DIR}/Unknown 1.0++")
target_link_libraries(UK Box2D ImGUI ${COMBINED_LIBS})
set_target_properties(UK PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${UK_LIB})
set_target_properties(UK PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${UK_LIB})
set_target_properties(UK PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${UK_LIB})


add_custom_command(TARGET UK POST_BUILD COMMAND python ${PROJECT_SOURCE_DIR}/tools/build/exportHeaders.py ${PROJECT_SOURCE_DIR} ${CMAKE_HOST_SYSTEM_NAME})