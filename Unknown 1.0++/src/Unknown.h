#ifndef UNKNOWN_H
#define UNKNOWN_H

#include <SDL.h>
#include <map>
#include <vector>
#include <functional>

#include "Timer.h"
#include "Utils.h"
#include "Scene/SceneManager.h"
#include "Event/EventManager.h"
#include "Image.h"
#include "UI.h"
#include "Engine/EngineConfig.h"
#include "Audio/SDLAudioEngine.h"
#include "Font/FontManager.h"
#include "core/SDL/SDLImageManager.h"
#include "core/window/SdlWindowManager.h"


namespace Unknown
{
    class SharedVariable;
    struct UIEvent;

	enum ErrorCodes
	{
		SDL_INITIALIZATION_FAIL = -10,
		SDL_WINDOW_CREATION_FAIL = -11,
		SDL_WINDOW_RENDERER_CREATION_FAIL = -12,
		SDL_WINDOW_PNG_INIT_FAIL = -13,
		SDL_WINDOW_TTF_INIT_FAIL = -14,
		SDL_RENDER_RECT_FAIL = -20,
		SDL_IMAGE_LOAD_FAIL = -21,
		SDL_IMAGE_TEXTURE_CREATE_FAIL = -22,
		SDL_MIXER_INIT_FAIL = -30,
		SDL_MIXER_OPEN_AUDIO_FAIL = -31
	};

	enum EngineState
	{
		UK_PRE_INIT, // Before renderer creation
		UK_INIT, // Creating renderer
		UK_POST_INIT, // Done creating render
		UK_LOOP, // Game loop started
		UK_QUIT // Game loop finished
	};

	class Unknown
	{
	private:
		Uint32 startTime = 0;
		double unprocessed = 0;
		Timer fpsCounter;

	public:
	    EngineConfig config;

		std::shared_ptr<Dimension<int>> screenSize;
		::Unknown::SceneManager globalSceneManager;
		EngineState currentState = UK_PRE_INIT;

        std::map<EventType, std::vector<EventHandler>> eventHandlers;
        std::map<std::string, SharedVariable*> variablelookup;
        std::map<std::string, std::function<void(std::shared_ptr<::Unknown::UIEvent>)> > UIListeners;

        ::SDLAudioEngine audioEngine;
        ::FontManager fontManager;
        ::SDLImageManager imageManager;
        ::SDLWindowManager windowManager;


		double tickSpeed = 0;

		int frames = 0;
		int ticks = 0;

        double fps = 0;
        double lastFrameTimeMS = 0;
        double lastUpdateTimeMS = 0;

		Unknown();

		void createWindow(const char* title, const int width, const int height, const int fps);
		void createWindow();

		void initGameLoop();
		void doSingleLoopIttr();

		void quit(const int exitCode);

		void checkEvents();
	};

	Unknown& getUnknown();

	#define UK_CREATE_WINDOW() ::Unknown::getUnknown().createWindow();
	#define UK_INIT_GAME() ::Unknown::getUnknown().initGameLoop()
}

#define UK_ADD_SCENE(x, y) ::Unknown::getUnknown().globalSceneManager.registerScene<x>(y)
#define UK_LOAD_SCENE(x) ::Unknown::getUnknown().globalSceneManager.loadScene(x)

#endif
