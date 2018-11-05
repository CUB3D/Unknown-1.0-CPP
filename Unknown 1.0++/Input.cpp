#include "stdafx.h"
#include "Input.h"

#include <SDL.h>

Unknown::Point<int> Unknown::getMouseLocation() {
	Point<int> p;
	SDL_GetMouseState(&p.x, &p.y);
	return p;
}