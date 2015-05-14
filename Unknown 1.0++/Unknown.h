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
		SDL_INITIALIZATION_FAIL = -1,
		SDL_WINDOW_CREATION_FAIL = -2,
		SDL_RENDER_RECT_FAIL = -3,
		SDL_IMAGE_LOAD_FAIL = -4,
		SDL_IMAGE_CONVERT_FAIL = -5
	};

	class Unknown
	{
	private:
		long startTime = 0;
		double unprocessed = 0;
		double tickSpeed = 0;
		Timer fpsCounter;

	public:
		SDL_Window* window;
		SDL_Surface* windowSurface;
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
