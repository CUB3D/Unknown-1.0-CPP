#include "Mouse.h"

#include <SDL.h>

glm::vec2 Unknown::getMouseLocation() {
    int x, y;
	SDL_GetMouseState(&x, &y);
	return glm::vec2(x, y);
}
