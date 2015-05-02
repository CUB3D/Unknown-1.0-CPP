#ifndef LOADER_H

#include "Sprite.h"
#include "Entity.h"

namespace Unknown
{
	namespace Loader
	{
		::Unknown::Sprite* loadSprite(const char* name);
		::Unknown::Entity* loadEntity(const char* name);

		#define UK_LOAD_SPRITE(x) ::Unknown::Loader::loadSprite(x);
		#define UK_LOAD_ENTITY(x) ::Unknown::Loader::loadEntity(x);
	}
}

#endif