//
// Created by cub3d on 29/07/2018.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_ENTITY_H
#define UNKNOWN_DEVELOPMENT_TOOL_ENTITY_H

#include "../Renderer/IRenderable.h"
#include "../IUpdateable.h"
#include <vector>
#include "../ITagable.h"
#include "../IInitable.h"
#include "../Types/Point.h"
#include "EntityPrototype.h"
#include <memory>

namespace Unknown {
    class EntityPrototype;

    class Entity : public IRenderable, public IUpdateable, public ITagable {
    public:
        Point<double> position;
        double angle;
        bool enabled;
        bool queueDissable;

        EntityPrototype prototype;


        Entity(EntityPrototype proto);

        virtual void update() override;
        virtual void render(double Xoffset, double Yoffset) const override;
        virtual void disable();
        virtual void queueDisable();


        void setPosition(double x, double y, double angle=0);
        void move(double x, double y);
        void rotate(double delta);


        virtual Rect<int> getRenderBounds() override;

        template<typename T>
        std::shared_ptr<T> getComponent() {
            for(auto& component : prototype.components) {
                auto casted = std::dynamic_pointer_cast<T>(component);
                if(casted) {
                    return casted;
                }
            }

            return nullptr;
        }

        virtual const std::string getTag() const override;
    };
}


#endif //UNKNOWN_DEVELOPMENT_TOOL_ENTITY_H
