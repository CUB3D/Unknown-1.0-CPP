set(IMGUI_SRC
        imgui.cpp
        imgui.h
        imconfig.h
        imgui_demo.cpp
        imgui_draw.cpp
        imgui_widgets.cpp
        imstb_rectpack.h
        imstb_textedit.h
        imstb_truetype.h
        imgui_internal.h
        imgui_impl_opengl3.cpp
        imgui_impl_opengl3.h
        imgui_impl_sdl.cpp
        imgui_impl_sdl.h
        )

add_library(ImGUI STATIC ${IMGUI_SRC})
target_include_directories(ImGUI PUBLIC ${SDL2_INCLUDE_DIR} ${GLM_INCLUDE_DIR})
target_link_libraries(ImGUI ${SDL2_LIBRARY})