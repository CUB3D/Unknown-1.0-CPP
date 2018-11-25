set(UK_PROJECT_NAME UKTest)

set(UK_TEST_SRC
        UnknownTest.cpp
        PhysicsTestScene.cpp
        RenderTestScene.cpp
        stdafx.cpp
        RenderTest2D.cpp)

add_executable(${UK_PROJECT_NAME} ${UK_TEST_SRC})
target_link_libraries(${UK_PROJECT_NAME} Unknown_Engine)
#set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${UK_PROJECT_NAME})
set_target_properties(${UK_PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Output/game/)
set_target_properties(${UK_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Output/game/)
set_target_properties(${UK_PROJECT_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Output/game/)

add_custom_command(TARGET ${UK_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_BINARY_DIR}/Output/UK/lib"
        $<TARGET_FILE_DIR:${UK_PROJECT_NAME}>)