set(UK_PROJECT_NAME UKTest)

set(UK_TEST_SRC
        UnknownTest.cpp
        PhysicsTestScene.cpp
        RenderTestScene.cpp
        stdafx.cpp
        RenderTest2D.cpp)

add_executable("UKTest" ${UK_TEST_SRC})
target_include_directories(UKTest PUBLIC ${UK_INCLUDE} ${COMBINED_INCLUDE})
target_link_libraries(UKTest UK LUA ${COMBINED_LIBS})
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT "UKTest")