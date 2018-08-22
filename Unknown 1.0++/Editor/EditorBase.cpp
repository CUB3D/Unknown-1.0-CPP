//
// Created by cub3d on 08/08/18.
//

#include "EditorBase.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include "../Unknown.h"

Unknown::EditorBase::EditorBase() : Scene("Editor") {

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetSwapInterval(0);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    auto& uk = getUnknown();

    ImGui_ImplSDL2_InitForOpenGL(uk.window, uk.glContext);
    ImGui_ImplOpenGL3_Init("#version 130");

    //TODO: profiler


    registerHook([&]{
        this->update();
    }, HookType::RENDER);
}

Unknown::EditorBase::~EditorBase() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void Unknown::EditorBase::update() {
    bool done;

    auto& uk = getUnknown();

    ImGuiIO& io = ImGui::GetIO();

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(uk.window);
    ImGui::NewFrame();

    ImGui::Begin("Profiler");

    ImGui::Text("GUI framerate %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    this->fps.push_front((float)getUnknown().lastFrameTimeMS);

    ImGui::PlotLines("Frame Time", [](void* d, int x) -> float {return (*(std::vector<float>*)d)[x];}, &fps, 10, 0);

    ImGui::End();

    ImGui::Begin("Scene Edit");
    bool b = true;
    ImGui::ShowDemoWindow(&b);
    ImGui::End();


    // Poll and handle events (inputs, window resize, etc.)
    // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
    // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
    // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
    // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
        ImGui_ImplSDL2_ProcessEvent(&event);
        if (event.type == SDL_QUIT)
            done = true;
        if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(uk.window))
            done = true;
    }

    // Rendering
    ImGui::Render();
    //SDL_GL_MakeCurrent(uk->window, uk->glContext);
    //glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
   // glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
