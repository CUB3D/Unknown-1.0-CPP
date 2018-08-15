#include "stdafx.h"
#include "Input.h"
#include "Log.h"

#include <SDL.h>
#include <vector>
#include <functional>
#include <map>
#include <string>
#include <fstream>
#include <sstream>

Unknown::Point<int> Unknown::getMouseLocation() {
	Point<int> p;
	SDL_GetMouseState(&p.x, &p.y);
	return p;
}