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
#include "IInitable.h"
#include "UI.h"
#include "Engine/EngineConfig.h"


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

    enum HookType
    {
        RENDER = 0,
        UPDATE = 1
    };

	class Unknown
	{
	private:
		Uint32 startTime = 0;
		double unprocessed = 0;
		Timer fpsCounter;

	public:
	    EngineConfig config;

		SDL_Surface* s;
		SDL_Window* window;
		SDL_Renderer* windowRenderer;
		std::shared_ptr<Dimension<int>> screenSize;
		::Unknown::SceneManager globalSceneManager;
		EngineState currentState = UK_PRE_INIT;

        std::map<HookType, std::vector<std::function<void()>>> hooks;
        std::map<EventType, std::vector<EventHandler>> eventHandlers;
        std::map<std::string, SharedVariable*> variablelookup;
		std::vector<::Unknown::IInitable<>*> lateInit;
        std::map<std::string, std::function<void(std::shared_ptr<::Unknown::UIEvent>)> > UIListeners;


		bool running = true;
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
		inline void doSingleLoopIttr();

		void quit(const int exitCode);

		void checkEvents();

		void update();
		void render();

		void updateWindow();
	};

	Unknown& getUnknown();

	void doSingleLoopItterC();
	
	#define UK_CREATE_WINDOW() ::Unknown::getUnknown().createWindow();
	#define UK_INIT_GAME() ::Unknown::getUnknown().initGameLoop()

	#define UK_GET_SCREEN_SIZE() ::Unknown::getUnknown()->screenSize


	void registerHook(std::function<void()> hook, HookType type);

	#define UK_RENDER(x) Unknown::registerHook(x, Unknown::HookType::RENDER);
	#define UK_UPDATE(x) Unknown::registerHook(x, Unknown::HookType::UPDATE);

	void callHooks(HookType type);
}

#define UK_ADD_SCENE(x) ::Unknown::getUnknown().globalSceneManager.add(x)
#define UK_LOAD_SCENE(x) ::Unknown::getUnknown().globalSceneManager.loadScene(x)

#endif
