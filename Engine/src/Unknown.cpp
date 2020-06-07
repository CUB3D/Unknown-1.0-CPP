#include "Unknown.h"

#include <chrono>
#include <SDL_mixer.h>

#include <Graphics/RenderingBackend.h>

#include <Settings/SettingsParser.h>
#include <Tracy.hpp>

#include "core/gameloop/GameLoop.h"


#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <core/log/Log.h>
#include <Imgui/GUI.h>
#include <SDL_image.h>
#include <Editor/CoreEditor.h>

#include "core/hook/HookRegistry.h"
#include "core/hook/Event.h"

// unknown class

Unknown::Unknown::Unknown() {
    ::Unknown::log_init();
}

void Unknown::Unknown::createWindow(const char* title, const int width, const int height, const int ups)
{
	ZoneScopedN("UK::CreateWindow");
	this->currentState = UK_INIT;

	UK_INFO("Creating window\n");

	windowManager.init(width, height);

	//TODO: remove
    this->screenSize = glm::vec2(width, height);

	getRendererBackend().intialise(config);

    getRendererBackend().createContext(windowManager.window);


	this->imageManager.init();
    this->fontManager.init();
    this->audioEngine.init();

	this->tickSpeed = 1000.0 / ups;
	this->startTime = SDL_GetTicks();

	HookRegistry<EngineInitEvent>::getInstance().invoke();
    HookRegistry<RenderEvent>::getInstance().add([=]{globalSceneManager.render();});
    HookRegistry<UpdateEvent>::getInstance().add([=]{globalSceneManager.update();});

	currentState = UK_POST_INIT;
}

void Unknown::Unknown::createWindow()
{
    ZoneScopedN("UK::createWindow");
    UK_INFO("Starting engine init");
	this->config = SettingsParser::parseSettings<EngineConfig>("Config.json");

	createWindow(config.title.c_str(), config.targetSize.x, config.targetSize.y, config.targetUPS);
}


void Unknown::Unknown::initGameLoop() {
    ZoneScopedN("UK::initGameLoop");

    this->currentState = UK_LOOP;

	mainGameLoop.init();
}

void Unknown::Unknown::doSingleLoopIttr() {
    ZoneScopedN("UK::doSingleLoopIttr");
    const char* err = SDL_GetError();
    if (strlen(err) > 0) {
        //TODO: move to imgui
        // UK_INFO("Error: %s\n", err);
        SDL_ClearError();
    }

    this->checkEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(windowManager.window);
    ImGui::NewFrame();

    long time = SDL_GetTicks();

    this->unprocessed += (time - startTime) / tickSpeed;
    this->startTime = time;

    while (this->unprocessed >= 1) {
        auto renderStartTime = std::chrono::high_resolution_clock::now();

        {
            ZoneScopedN("UK::update");
            HookRegistry<UpdateEvent>::getInstance().invoke();
        }

        auto renderFinishTime = std::chrono::high_resolution_clock::now();
        this->lastUpdateTimeMS = this->lastFrameTimeMS = std::chrono::duration_cast<std::chrono::nanoseconds>(renderFinishTime-renderStartTime).count() / 1000000.0;

        this->ticks++;
        this->unprocessed--;
    }

    getRendererBackend().newFrame();

    auto renderStartTime = std::chrono::high_resolution_clock::now();
    {
        ZoneScopedN("UK::render");

        if(config.editing) {
            CoreEditor::getInstance().render();
        }

        HookRegistry<RenderEvent>::getInstance().invoke();
    }
    auto renderFinishTime = std::chrono::high_resolution_clock::now();
    this->lastFrameTimeMS = std::chrono::duration_cast<std::chrono::nanoseconds>(renderFinishTime-renderStartTime).count() / 1000000.0;

    // Draw the imgui window
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    this->frames++;

    getRendererBackend().endFrame();
    FrameMark;

    if (fpsCounter.isTickComplete()) {
        UK_INFO("Frames: {}, Ticks: {}", this->frames, this->ticks);
        this->fps = this->frames;

        this->frames = 0;
        this->ticks = 0;
    }
}

void Unknown::Unknown::checkEvents() {
    ZoneScopedN("UK::EventCheck");
	SDL_Event evnt;
    ImGuiIO& io = ImGui::GetIO();
    bool postImguiEvents = io.WantCaptureKeyboard || io.WantCaptureMouse;

	while (SDL_PollEvent(&evnt) != 0) {
	    if(postImguiEvents) {
            ImGui_ImplSDL2_ProcessEvent(&evnt);
            continue;
        }

		Uint32 eventType = evnt.type;

		if (eventType == SDL_QUIT) {
			this->quit(0);
		}

		if (eventType == SDL_KEYDOWN || eventType == SDL_KEYUP) {

			HookRegistry<KeyPressEvent>::getInstance().invoke(KeyPressEvent {
                    evnt.key.keysym.sym,
                eventType == SDL_KEYDOWN
			});
		}

		if (eventType == SDL_MOUSEBUTTONDOWN || eventType == SDL_MOUSEBUTTONUP) {
			HookRegistry<MouseEvent>::getInstance().invoke(MouseEvent {
                    evnt.button.button,
                    eventType == SDL_MOUSEBUTTONDOWN,
                    glm::vec2(evnt.button.x, evnt.button.y)
			});
		}

		if(eventType == SDL_WINDOWEVENT) {
            if (evnt.window.event == SDL_WINDOWEVENT_RESIZED) {
                this->screenSize = glm::vec2(evnt.window.data1, evnt.window.data2);

                auto evt = ResizeEvent {
                        (int) this->screenSize.x,
                        (int) this->screenSize.y
                };
                HookRegistry<ResizeEvent>::getInstance().invoke(evt);
            }
        }
	}
}

void Unknown::Unknown::quit(const int exitCode) {
    ZoneScopedN("UK::quit");

    this->currentState = UK_QUIT;

    // All Images must have been destroyed or this will cause a sigsev
    getRendererBackend().quit();

	SDL_DestroyWindow(this->windowManager.window);

	this->audioEngine.shutdown();

	SDL_Quit();

	exit(exitCode);
}

Unknown::Unknown& Unknown::getUnknown() {
    ZoneScopedN("UK::getUnknown");
    static Unknown instance;

	return instance;
}
