#ifndef INPUT_H
#define INPUT_H

#include "Event/EventManager.h"
#include "Event/Event.h"

#include "Utils.h"

#include <vector>
#include <functional>
#include <map>

namespace Unknown
{
	// Generic input

	// Mouse input

	Point<int> getMouseLocation();
#define UK_GET_MOUSE_POS(p) SDL_GetMouseState(&p.x, &p.y)
}

#endif
