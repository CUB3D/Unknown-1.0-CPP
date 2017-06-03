#include "stdafx.h"
#include "Unknown.h"

#include "Python.h"
#include <SDL.h>
#include <iostream>
#include <map>

#include "Input.h"
#include "UI2D.h"
#include "Colour.h"

#include <ios>
#include <fstream>
#include <string>
#include "document.h"
#include "PythonScript.h"
#include "Utils.h"

#include <chrono>
#include <SDL_ttf.h>

// unknown class

Unknown::Unknown::Unknown()
{
}

void Unknown::Unknown::createWindow(const char* title, const int width, const int height, const int ups)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Error: SDL failed to initialise, %s\n", SDL_GetError());
		quit(ErrorCodes::SDL_INITIALIZATION_FAIL);
	}

	this->window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

	if (!window)
	{
		printf("Error: SDL failed to create a window, %s\n", SDL_GetError());
		quit(ErrorCodes::SDL_WINDOW_CREATION_FAIL);
	}

	this->windowRenderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);

	if (!windowRenderer)
	{
		printf("Error: SDL failed to create renderer, %s\n", SDL_GetError());
		quit(ErrorCodes::SDL_WINDOW_RENDERER_CREATION_FAIL);
	}

	SDL_SetRenderDrawColor(this->windowRenderer, 0, 0, 0, 0); // Black

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
	{
		printf("Error: SDL failed to initialise PNG loading, %s\n", IMG_GetError());
		quit(ErrorCodes::SDL_WINDOW_PNG_INIT_FAIL);
	}

    if(TTF_Init() == -1)
    {
        printf("Error: SDL failed to initialise TTF handling, %s\n", TTF_GetError());
        quit(ErrorCodes::SDL_WINDOW_TTF_INIT_FAIL);
    }

	this->tickSpeed = 1000.0 / ups;
	this->startTime = SDL_GetTicks();

    //Could be a memory leak
	this->screenSize = new Dimension<int> { width, height };

	::Unknown::Python::getInterpreter()->init();
}

void Unknown::Unknown::createWindow()
{
	int height = 0;
	int width = 0;
	std::string title;
    int ups = 60;

	rapidjson::Document doc = readJSONFile("Config.json");

	rapidjson::Value* heightValue = getValue("Height", rapidjson::Type::kNumberType, doc);

	if (heightValue)
	{
		height = heightValue->GetInt();
	}

	rapidjson::Value* widthValue = getValue("Width", rapidjson::Type::kNumberType, doc);

	if (widthValue)
	{
		width = widthValue->GetInt();
	}

	rapidjson::Value* titleValue = getValue("Title", rapidjson::Type::kStringType, doc);

	if (titleValue)
	{
		title = titleValue->GetString();
	}

    rapidjson::Value* upsValue = getValue("ups", rapidjson::Type::kNumberType, doc);

    if(upsValue)
    {
        ups = upsValue->GetInt();
    }
    else
    {
        printf("[UK] No update speed specified, defaulting to 60tps\n");
    }

	createWindow(title.c_str(), width, height, ups);
}

void Unknown::Unknown::initGameLoop()
{
	initKeySystem();

	while (running)
	{
		this->checkEvents();

		long time = SDL_GetTicks();

		this->unprocessed += (time - startTime) / tickSpeed;
		this->startTime = time;

		while (this->unprocessed >= 1)
		{
            auto renderStartTime = std::chrono::high_resolution_clock::now();
			this->update();
            auto renderFinishTime = std::chrono::high_resolution_clock::now();
            this->lastUpdateTimeMS = this->lastFrameTimeMS = std::chrono::duration_cast<std::chrono::nanoseconds>(renderFinishTime-renderStartTime).count() / 1000000.0;

			this->ticks++;
			this->unprocessed--;
		}

		this->clearScreen();

        auto renderStartTime = std::chrono::high_resolution_clock::now();
		this->render();
		auto renderFinishTime = std::chrono::high_resolution_clock::now();
        this->lastFrameTimeMS = std::chrono::duration_cast<std::chrono::nanoseconds>(renderFinishTime-renderStartTime).count() / 1000000.0;
        this->fps = 1000 / this->lastFrameTimeMS;

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
	SDL_Event evnt;

	while (SDL_PollEvent(&evnt) != 0)
	{
		Uint32 eventType = evnt.type;

		if (eventType == SDL_QUIT)
		{
			this->quit(0);
		}

		if (eventType == SDL_KEYDOWN || eventType == SDL_KEYUP)
		{
			KeyEvent evt;

			evt.SDLCode = evnt.key.keysym.sym;
			evt.keyState = (eventType == SDL_KEYDOWN) ? InputState::PRESSED : InputState::RELEASED;

			postKeyEvent(evt);
		}

		if (eventType == SDL_MOUSEBUTTONDOWN || eventType == SDL_MOUSEBUTTONUP)
		{
			MouseEvent evt;

			evt.SDLButtonCode = evnt.button.button;
			evt.buttonState = (eventType == SDL_MOUSEBUTTONDOWN) ? InputState::PRESSED : InputState::RELEASED;
			evt.location.x = evnt.button.x;
			evt.location.y = evnt.button.y;

			postMouseEvent(evt);
		}
	}
}

void Unknown::Unknown::clearScreen()
{
	UK_SET_COLOUR(Colour::BLACK);
	SDL_RenderClear(this->windowRenderer);
}

void Unknown::Unknown::quit(const int exitCode)
{
	SDL_DestroyRenderer(this->windowRenderer);
	this->windowRenderer = NULL;
	SDL_DestroyWindow(this->window);
	this->window = NULL;

	exitKeySystem();

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
	SDL_RenderPresent(this->windowRenderer);
}

Unknown::Unknown* Unknown::instance;

Unknown::Unknown* Unknown::getUnknown()
{
	if (instance == nullptr)
		instance = new Unknown();

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
