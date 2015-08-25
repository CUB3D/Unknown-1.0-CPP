#ifndef LOADER_H

#include "Sprite.h"
#include "Entity.h"
#include "Animation.h"

#include <map>

namespace Unknown
{
	namespace Loader
	{
		extern std::map<const char*, Sprite*> spritePool;
		extern std::map<const char*, Entity*> entityPool;
		extern std::map<const char*, Graphics::Image*> imagePool;

		::Unknown::Sprite* loadSprite(const char* name);
		::Unknown::Entity* loadEntity(const char* name);
		::Unknown::Graphics::Animation* loadAnimation(const char* name);
		::Unknown::Graphics::Image* loadImage(const char* name);
	}
}

#define UK_LOAD_SPRITE(x) ::Unknown::Loader::loadSprite(x)
#define UK_LOAD_ENTITY(x) ::Unknown::Loader::loadEntity(x)
#define UK_LOAD_ANIMATION(x) ::Unknown::Loader::loadAnimation(x)
#define UK_LOAD_IMAGE(name) ::Unknown::Loader::loadImage(name);

#endif