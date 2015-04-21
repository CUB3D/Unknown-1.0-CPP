#include "stdafx.h"
#include "Unknown.h"

#include <SDL.h>
#include <iostream>
#include <map>

#include "Input.h"
#include "UI2D.h"
#include "Colour.h"

// unknown class

Unknown::Unknown::Unknown()
{
}

void Unknown::Unknown::createWindow(const char* title, const int width, const int height)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Error: SDL failed to initalize, %s\n", SDL_GetError());
		quit(ErrorCodes::SDL_INITIALIZATION_FAIL);
	}

	this->window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		printf("Error: SDL failed to create a window, %s\n", SDL_GetError());
		quit(ErrorCodes::SDL_WINDOW_CREATION_FAIL);
	}

	this->windowSurface = SDL_GetWindowSurface(this->window);

	int fps = 60;

	this->tickSpeed = 1000.0 / fps;
	this->startTime = SDL_GetTicks();

	this->screenSize = new Dimension { width, height };
}

void Unknown::Unknown::initGameLoop()
{
	while (running)
	{
		this->checkEvents();

		long time = SDL_GetTicks();

		this->unprocessed += (time - startTime) / tickSpeed;
		this->startTime = time;

		while (this->unprocessed >= 1)
		{
			this->update();

			this->ticks++;
			this->unprocessed--;
		}

		this->clearScreen();

		this->render();

		this->frames++;

		this->updateWindow();

		if (fpsCounter.isTickComplete())
		{
			std::cout << "Frames: " << this->frames << ", Ticks: " << this->ticks << std::endl;

			this->frames = 0;
			this->ticks = 0;
		}
	}
}

void Unknown::Unknown::checkEvents()
{
	SDL_Event* evnt = new SDL_Event();

	while (SDL_PollEvent(evnt) != 0)
	{
		Uint32 eventType = evnt->type;

		if (eventType == SDL_QUIT)
		{
			this->quit(0);
		}

		if (eventType == SDL_KEYDOWN || eventType == SDL_KEYUP)
		{
			KeyEvent evt;

			evt.SDLCode = evnt->key.keysym.sym;
			evt.keyState = (eventType == SDL_KEYDOWN) ? InputState::PRESSED : InputState::RELEASED;

			postKeyEvent(evt);
		}

		if (eventType == SDL_MOUSEBUTTONDOWN || eventType == SDL_MOUSEBUTTONUP)
		{
			MouseEvent evt;

			evt.SDLButtonCode = evnt->button.button;
			evt.buttonState = (eventType == SDL_MOUSEBUTTONDOWN) ? InputState::PRESSED : InputState::RELEASED;

			postMouseEvent(evt);
		}
	}
}

void Unknown::Unknown::clearScreen()
{
	Graphics::drawRect(0, 0, (int)screenSize->width, (int)screenSize->height, Colour(0, 0, 0));
}

void Unknown::Unknown::quit(const int exitCode)
{
	SDL_DestroyWindow(this->window);
	this->window = NULL;
	this->windowSurface = NULL;

	SDL_Quit();

	exit(exitCode);
}

void Unknown::Unknown::update()
{
	callHooks(HookType::UPDATE);
}

void Unknown::Unknown::render()
{
	callHooks(HookType::RENDER);
}

void Unknown::Unknown::updateWindow()
{
	SDL_UpdateWindowSurface(this->window);
}

Unknown::Unknown* Unknown::instance;

Unknown::Unknown* Unknown::getUnknown()
{
	if (instance == nullptr)
		instance = new Unknown;

	return instance;
}

std::map < Unknown::HookType, std::vector < void(*) (void) > > Unknown::hooks;

void Unknown::registerHook(void(*hook) (void), HookType type)
{
	std::vector < void(*) (void) > vec = hooks[type];

	vec.push_back(hook);

	hooks[type] = vec;
}

void Unknown::callHooks(HookType type)
{
	std::vector < void(*) (void) > vec = hooks[type];

	for (int i = 0; i < vec.size(); i++)
		vec[i]();
}