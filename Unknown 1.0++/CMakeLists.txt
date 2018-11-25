FILE(GLOB_RECURSE UK_ENGINE_SRC "*.c*" )
FILE(GLOB_RECURSE UK_ENGINE_INCLUDES "*.h*")

# Remove seperate modules
list(FILTER UK_ENGINE_SRC EXCLUDE REGEX "python")
list(FILTER UK_ENGINE_SRC EXCLUDE REGEX "lua")

# Add sub projects
add_subdirectory(Box2D)
add_subdirectory(Imgui)
#add_subdirectory(scripting/lua)
#add_subdirectory(scripting/python)

set(UK_INCLUDE "${UK_DIR}/Unknown 1.0++")

add_library(UK SHARED ${UK_ENGINE_SRC} ${UK_ENGINE_INCLUDES})
target_include_directories(UK PUBLIC ${COMBINED_INCLUDE} ${UK_INCLUDE})
target_link_libraries(UK Box2D ImGUI ${COMBINED_LIBS})
set_target_properties(UK PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Output/UK/lib)
set_target_properties(UK PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Output/UK/lib)
set_target_properties(UK PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Output/UK/lib)

# Create header dir
INSTALL(DIRECTORY "${UK_DIR}/Unknown 1.0++/"
		DESTINATION ${CMAKE_BINARY_DIR}/Output/UK/include
		FILES_MATCHING PATTERN "*.h*")

#---Copy lib dlls---

# SDL
INSTALL(DIRECTORY "${UK_DIR}/Libs/SDL2/lib/x64/"
		DESTINATION ${CMAKE_BINARY_DIR}/Output/UK/lib
		FILES_MATCHING PATTERN "*.dll")

# SDL_image
INSTALL(DIRECTORY "${UK_DIR}/Libs/SDL2_image/lib/x64/"
		DESTINATION ${CMAKE_BINARY_DIR}/Output/UK/lib
		FILES_MATCHING PATTERN "*.dll")

# SDL_ttf
INSTALL(DIRECTORY "${UK_DIR}/Libs/SDL2_ttf/lib/x64/"
		DESTINATION ${CMAKE_BINARY_DIR}/Output/UK/lib
		FILES_MATCHING PATTERN "*.dll")

# SDL_mixer
INSTALL(DIRECTORY "${UK_DIR}/Libs/SDL2_mixer/lib/x64/"
		DESTINATION ${CMAKE_BINARY_DIR}/Output/UK/lib
		FILES_MATCHING PATTERN "*.dll")

# Run install after building
#add_custom_command(TARGET UK
#				   POST_BUILD
#				   COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target install)

add_library(Unknown_Engine INTERFACE)
target_link_libraries(Unknown_Engine INTERFACE UK ${COMBINED_LIBS})
target_include_directories(Unknown_Engine INTERFACE ${UK_INCLUDE} ${COMBINED_INCLUDE})
