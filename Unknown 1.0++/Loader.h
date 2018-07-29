#ifndef LOADER_H
			//postKeyEvent(evt);

#include "Sprite.h"
#include "Entity/Entity.h"
#include "Animation.h"
#include "UI.h"

#include <map>

namespace Unknown
{
    namespace Loader
    {
        extern std::map<const char*, std::unique_ptr<Sprite>> spritePool;
        extern std::map<const char*, std::unique_ptr<Graphics::Image>> imagePool;

        ::Unknown::Sprite* loadSprite(const char* name);
        std::shared_ptr<::Unknown::Entity> loadEntity(const std::string& name);
        ::Unknown::Graphics::Animation* loadAnimation(const char* name);
        std::unique_ptr<::Unknown::Graphics::Image> loadImage(const char* name);
        ::Unknown::UIContainer loadUI(const std::string &name);
    }
}

#define UK_LOAD_SPRITE(x) ::Unknown::Loader::loadSprite(x)
#define UK_LOAD_ENTITY(x) ::Unknown::Loader::loadEntity(x)
#define UK_LOAD_ANIMATION(x) ::Unknown::Loader::loadAnimation(x)
#define UK_LOAD_IMAGE(name) ::Unknown::Loader::loadImage(name)

#endif