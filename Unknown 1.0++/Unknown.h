#ifndef UNKNOWN_H
#define UNKNOWN_H

#include <SDL.h>
#include <map>
#include <vector>

#include "Timer.h"
#include "Utils.h"

namespace Unknown
{
	enum ErrorCodes
	{
		SDL_INITIALIZATION_FAIL = -10,
		SDL_WINDOW_CREATION_FAIL = -11,
		SDL_WINDOW_RENDERER_CREATION_FAIL = -12,
		SDL_WINDOW_PNG_INIT_FAIL = -13,
		SDL_RENDER_RECT_FAIL = -20,
		SDL_IMAGE_LOAD_FAIL = -21,
		SDL_IMAGE_TEXTURE_CREATE_FAIL = -22,
	};

	class Unknown
	{
	private:
		long startTime = 0;
		double unprocessed = 0;
		double tickSpeed = 0;
		Timer fpsCounter;

	public:
		SDL_Surface* s;
		SDL_Window* window;
		SDL_Renderer* windowRenderer;
		const Dimension<int>* screenSize;

		bool running = true;

		int frames = 0;
		int ticks = 0;

		Unknown();

		void createWindow(const char* title, const int width, const int height);
		void createWindow();

		void initGameLoop();

		void quit(const int exitCode);

		void checkEvents();
		void clearScreen();

		void update();
		void render();

		void updateWindow();
	};

	extern Unknown* instance;

	Unknown* getUnknown();
	
	#define UK_CREATE_WINDOW() ::Unknown::getUnknown()->createWindow();
	#define UK_INIT_GAME() ::Unknown::getUnknown()->initGameLoop()

	#define UK_GET_SCREEN_SIZE() ::Unknown::getUnknown()->screenSize

	enum HookType
	{
		RENDER,
		UPDATE
	};

	extern std::map < HookType, std::vector < void(*) (void) > > hooks;

	void registerHook(void(*hook) (void), HookType type);

	#define UK_RENDER(x) Unknown::registerHook(x, Unknown::HookType::RENDER);
	#define UK_UPDATE(x) Unknown::registerHook(x, Unknown::HookType::UPDATE);

	void callHooks(HookType type);
}

#endif
