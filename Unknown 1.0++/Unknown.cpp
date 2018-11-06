#include "stdafx.h"
#include "Unknown.h"

#include <iostream>
#include <map>

#include "Input.h"
#include "UI2D.h"
#include "Colour.h"

#include <ios>
#include <fstream>
#include <string>
#include "document.h"
#include "Utils.h"

#include <chrono>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "GL/GL.h"

#include "Graphics/RenderingBackend.h"

#include "Settings/SettingsParser.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "Event/Event.h"
#include "Event/EventManager.h"
#include "Image.h"
#include "Log.h"
#include "Imgui/GUI.h"

// unknown class

Unknown::Unknown::Unknown() {}

void Unknown::Unknown::createWindow(const char* title, const int width, const int height, const int ups)
{
	this->currentState = UK_INIT;

    this->screenSize = std::make_shared<Dimension<int>>(width, height);

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
	    UK_LOG_ERROR("SDL failed to initialise: ", SDL_GetError());
		quit(ErrorCodes::SDL_INITIALIZATION_FAIL);
	}

	getRendererBackend()->intialise(config);

	this->window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	if (!window) {
	    UK_LOG_ERROR("SDL failed to create window: ", SDL_GetError());
		quit(ErrorCodes::SDL_WINDOW_CREATION_FAIL);
	}

	this->windowRenderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
	if (!windowRenderer) {
	    UK_LOG_ERROR("SDL failed to create renderer: ", SDL_GetError());
		quit(ErrorCodes::SDL_WINDOW_RENDERER_CREATION_FAIL);
	}

    getRendererBackend()->createContext(window);

//	SDL_SetRenderDrawColor(this->windowRenderer, 0, 0, 0, 0); // Black


#ifndef __EMSCRIPTEN__ // SDL_image isn't linked against libpng in emscripten, it uses browser decoding so init isnt needed
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
	{
		printf("Error: SDL failed to initialise PNG loading, %s\n", IMG_GetError());
		quit(ErrorCodes::SDL_WINDOW_PNG_INIT_FAIL);
	}
#else
	printf("Using emscripten, not initialsing SDL_image\n");
#endif

    if(TTF_Init() == -1)
    {
        printf("Error: SDL failed to initialise TTF handling, %s\n", TTF_GetError());
        quit(ErrorCodes::SDL_WINDOW_TTF_INIT_FAIL);
    }

    if(SDL_Init(SDL_INIT_AUDIO) == -1) {
		printf("Error: SDL failed to initialise audio handling, %s\n", Mix_GetError());
		quit(ErrorCodes::SDL_MIXER_INIT_FAIL);
	}

    if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
        printf("Failed to setup audio mixer %s\n", Mix_GetError());
        quit(ErrorCodes::SDL_MIXER_OPEN_AUDIO_FAIL);
    }

    Mix_AllocateChannels(64);

	this->tickSpeed = 1000.0 / ups;
	this->startTime = SDL_GetTicks();


	// All of the images that were created early (i.e. given as args to sprites in constructor)
	// Need to have init called as a render context is needed to make texture from image
	// This specifically needs to be done before any images are rendered but after windowRenderer creation
	UK_LOG_INFO("Performing late init for", intToString(lateInit.size()), " objects");
	for(auto& initable : lateInit) {
		initable->init();
	}

    registerHook([=]{globalSceneManager.render();}, RENDER);
    registerHook([=]{globalSceneManager.update();}, UPDATE);

	currentState = UK_POST_INIT;
}

void Unknown::Unknown::createWindow()
{
	UK_LOG_INFO("Starting engine init");
	this->config = SettingsParser::parseSettings<EngineConfig>("Config.json");

	createWindow(config.title.c_str(), config.targetWidth, config.targetHeight, config.targetUPS);
}

void Unknown::Unknown::initGameLoop()
{
	this->currentState = UK_LOOP;

#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(doSingleLoopItterC, 0, 1);
#else
	while (running) {
        doSingleLoopIttr();
	}
#endif
}

void ::Unknown::doSingleLoopItterC() {
	::Unknown::getUnknown().doSingleLoopIttr();
}

void Unknown::Unknown::doSingleLoopIttr() {
    const char* err = SDL_GetError();
    if (strlen(err) > 0) {
        //TODO: move to imgui
        // printf("Error: %s\n", err);
        SDL_ClearError();
    }

    this->checkEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(window);
    ImGui::NewFrame();

    long time = SDL_GetTicks();

    this->unprocessed += (time - startTime) / tickSpeed;
    this->startTime = time;

    while (this->unprocessed >= 1) {
        auto renderStartTime = std::chrono::high_resolution_clock::now();
        this->update();
        auto renderFinishTime = std::chrono::high_resolution_clock::now();
        this->lastUpdateTimeMS = this->lastFrameTimeMS = std::chrono::duration_cast<std::chrono::nanoseconds>(renderFinishTime-renderStartTime).count() / 1000000.0;

        this->ticks++;
        this->unprocessed--;
    }

    auto renderStartTime = std::chrono::high_resolution_clock::now();
    getRendererBackend()->clearScreen();
    this->render();
    auto renderFinishTime = std::chrono::high_resolution_clock::now();
    this->lastFrameTimeMS = std::chrono::duration_cast<std::chrono::nanoseconds>(renderFinishTime-renderStartTime).count() / 1000000.0;

    // Draw the imgui window
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    this->frames++;

    this->updateWindow();

    if (fpsCounter.isTickComplete()) {
        std::cout << "Frames: " << this->frames << ", Ticks: " << this->ticks << std::endl;
        this->fps = this->frames;

        this->frames = 0;
        this->ticks = 0;
    }
}

void Unknown::Unknown::checkEvents()
{
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

		Event evt;
		evt.original = &evnt;

		if (eventType == SDL_KEYDOWN || eventType == SDL_KEYUP) {
			evt.key.SDLCode = evnt.key.keysym.sym;
			evt.key.keyState = (eventType == SDL_KEYDOWN) ? InputState::PRESSED : InputState::RELEASED;

            postEvent(ET_KEYPRESS, evt);
		}

		if (eventType == SDL_MOUSEBUTTONDOWN || eventType == SDL_MOUSEBUTTONUP) {
			evt.mouse.SDLButtonCode = evnt.button.button;
			evt.mouse.buttonState = (eventType == SDL_MOUSEBUTTONDOWN) ? InputState::PRESSED : InputState::RELEASED;
			evt.mouse.location.x = evnt.button.x;
			evt.mouse.location.y = evnt.button.y;

			postEvent(ET_MOUSEBUTTON, evt);
		}

		if(eventType == SDL_WINDOWEVENT) {
            if (evnt.window.event == SDL_WINDOWEVENT_RESIZED) {
                this->screenSize = std::make_shared<Dimension<int>>(evnt.window.data1, evnt.window.data2);

                evt.resize.newWidth = this->screenSize->width;
                evt.resize.newHeight = this->screenSize->height;

                postEvent(ET_WINDOW_RESIZE, evt);
            }
        }
	}
}

void Unknown::Unknown::quit(const int exitCode) {
	this->currentState = UK_QUIT;

    // All Images must have been destroyed or this will cause a sigsev
    getRendererBackend()->quit();

	//SDL_DestroyRenderer(this->windowRenderer);
	SDL_DestroyWindow(this->window);
	this->windowRenderer = nullptr;
	this->window = nullptr;

	Mix_CloseAudio();

	SDL_Quit();

	exit(exitCode);
}

void Unknown::Unknown::update() {
	callHooks(HookType::UPDATE);
}

void Unknown::Unknown::render() {
	callHooks(HookType::RENDER);
}

void Unknown::Unknown::updateWindow() {
    SDL_GL_SwapWindow(window);
}

Unknown::Unknown& Unknown::getUnknown() {
    static Unknown instance;

	return instance;
}

void Unknown::registerHook(std::function<void()> hook, HookType type) {
	printf("Registering a hook %d\n", (int)type);

	auto& hooks = getUnknown().hooks;

	if(hooks.find(type) == hooks.end()) {
//	    // If there is no hooks
        hooks[type] = std::vector<std::function<void()>>();
	}

	auto vec = hooks[type];

	vec.push_back(hook);

	hooks[type] = vec;
}

void Unknown::callHooks(HookType type) {
    for(auto& hook : getUnknown().hooks[type]) {
        hook();
    }
}
