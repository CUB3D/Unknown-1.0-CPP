#ifndef LOADER_H
			//postKeyEvent(evt);

#include "Entity/Entity.h"
#include "Animation.h"
#include "UI.h"

#include <map>

namespace Unknown
{
    namespace Loader
    {
        extern std::map<std::string, std::shared_ptr<Graphics::Image>> imagePool;


        std::shared_ptr<Entity> loadEntityAt(const std::string &name, Scene &scene, double x, double y);
        std::shared_ptr<Entity> loadEntity(const std::string &name, Scene& scene);


        ::Unknown::Graphics::Animation* loadAnimation(const char* name);
        std::shared_ptr<::Unknown::Graphics::Image> loadImage(const std::string& name);
        ::Unknown::UIContainer loadUI(const std::string &name);
    }
}

#define UK_LOAD_ENTITY(x) ::Unknown::Loader::loadEntity(x, *this)
#define UK_LOAD_ANIMATION(x) ::Unknown::Loader::loadAnimation(x)
#define UK_LOAD_IMAGE(name) ::Unknown::Loader::loadImage(name)

#endif