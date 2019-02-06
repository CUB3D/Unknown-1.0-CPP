//
// Created by cub3d on 08/08/18.
//

#include "EditorBase.h"
#include <Unknown.h>
#include <Entity/Entity.h>
#include <Loader.h>
#include <Event/Event.h>
#include <UI2D.h>
#include <Imgui/GUI.h>

Unknown::EditorBase::EditorBase(const std::string &under) : Scene(), under(under), editing(false) {

    //SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    //SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    //SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    //SDL_GL_SetSwapInterval(0);

   // auto& uk = getUnknown();

    //ImGui_ImplSDL2_InitForOpenGL(uk.window, uk.glContext);
   // ImGui_ImplOpenGL3_Init("#version 130");

    //TODO: profiler

    registerEventHandler(ET_MOUSEBUTTON, "editSelect", [this](Event& evt){
        if(evt.mouse.buttonState == PRESSED) {
            auto lc = getLastScene();
            if(!lc)
                return;
            for(auto& e : lc->entities) {
                if(e->getRenderBounds().contains(evt.mouse.location)) {
                    this->selected = e;
                    this->entityEditors.emplace_back(e);
                }
            }
        }
    });
}

Unknown::EditorBase::~EditorBase() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}


void Unknown::EditorBase::update() {
    //TODO: dont update scene when editing, ability to disable editor (e.g. menu bar) and abillity to
    if(!editing)
        getLastScene()->update();

    getLastScene()->render();

    auto& uk = getUnknown();

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(uk.window);
    ImGui::NewFrame();

    ImGui::BeginMainMenuBar();
    createMenuBar();
    ImGui::EndMainMenuBar();

    if(!editing) {
        ImGui::EndFrame();
        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        return;
    }


    ImGui::Begin("Profiler");

    ImGui::Text("GUI framerate %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::Text("Core framerate %.5lf ms/frame (%.1lf FPS)", uk.lastFrameTimeMS, uk.fps);

    this->fps.push_front((float)getUnknown().lastFrameTimeMS);

    ImGui::PlotLines("Frame Time", [](void* d, int x) -> float {return (*(std::vector<float>*)d)[x];}, &fps, 10, 0);

    ImGui::End();

    for(auto& ent : entityEditors) {
        ent.populateGui();
    }

    ImGui::EndFrame();
    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Unknown::EditorBase::render() const {
    if(selected) {
        int x = selected->getRenderBounds().center().x;
        int y = selected->getRenderBounds().center().y;
        ::Unknown::Graphics::drawRect(x, y, 50, 5, 0, UK_COLOUR_RGB(255, 0, 0));
        ::Unknown::Graphics::drawRect(x, y - 50, 5, 50, 0, UK_COLOUR_RGB(0, 255, 0));
    }
}

std::shared_ptr<::Unknown::Scene> Unknown::EditorBase::getLastScene() const {
    auto& gcm = ::Unknown::getUnknown().globalSceneManager;
    return gcm.scenes[gcm.scenes.size() - 2].second;
}

void Unknown::EditorBase::createMenuBar() {
    //ImGui::MenuItem("Editor");
    ImGui::Checkbox("Editor", &this->editing);
}
