#ifndef LOADER_H

#include "Entity/Entity.h"
#include "Animation.h"
#include "UI.h"

#include <map>
#include <Entity/EntityPrototype.h>
#include "Model/MeshContainer.h"

namespace Unknown
{
    namespace Loader
    {
        extern std::map<std::string, std::shared_ptr<Graphics::Image>> imagePool;


        std::shared_ptr<::Unknown::Entity> loadEntityAt(const std::string &name, double x, double y);
        std::shared_ptr<::Unknown::Entity> loadEntity(const std::string &name);
        EntityPrototype& loadEntityPrototype(const std::string& name);


        ::Unknown::Graphics::Animation* loadAnimation(const char* name);
        std::shared_ptr<::Unknown::Graphics::Image> loadImage(const std::string& name);
        ::Unknown::UIContainer loadUI(const std::string &name);

        std::shared_ptr<MeshContainer> loadModel(const std::string& name);
    }
}

#define UK_LOAD_ENTITY(x) ::Unknown::Loader::loadEntity(x)
#define UK_LOAD_ANIMATION(x) ::Unknown::Loader::loadAnimation(x)
#define UK_LOAD_IMAGE(name) ::Unknown::Loader::loadImage(name)

#endif