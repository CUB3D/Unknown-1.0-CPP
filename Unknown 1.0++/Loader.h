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
        std::shared_ptr<::Unknown::Entity> loadEntityAt(const std::string &name, double x, double y);
        std::shared_ptr<::Unknown::Entity> loadEntity(const std::string &name);
        EntityPrototype loadEntityPrototype(const std::string &name);


        Animation* loadAnimation(const char* name);
        ::Unknown::UIContainer loadUI(const std::string &name);

        std::shared_ptr<MeshContainer> loadModel(const std::string& name);
    }
}

#define UK_LOAD_ENTITY(x) ::Unknown::Loader::loadEntity(x)
#define UK_LOAD_ENTITY_AT(name, x, y) ::Unknown::Loader::loadEntityAt(name, x, y)
#define UK_LOAD_ANIMATION(x) ::Unknown::Loader::loadAnimation(x)
#define UK_LOAD_IMAGE(name) ::Unknown::Loader::loadImage(name)

#endif