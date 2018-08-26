//
// Created by cub3d on 29/07/2018.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_ENTITY_H
#define UNKNOWN_DEVELOPMENT_TOOL_ENTITY_H

#include "Component.h"
#include "../Renderer/IRenderable.h"
#include "../IUpdateable.h"
#include <vector>
#include "../Utils.h"
#include "../ITagable.h"

namespace Unknown
{
    class Component;

    class Entity : public IRenderable, public IUpdateable, public ITagable
    {
    public:
        std::vector<std::shared_ptr<Component>> components;

        Dimension<double> size;
        Point<double> position;
        const std::string tag;
        double angle;
        bool enabled;
        bool queueDissable;


        Entity(const std::string& str);

        virtual void update() override;
        virtual void render(double Xoffset, double Yoffset) const override;
        virtual void disable();
        virtual void queueDisable();


        void setPosition(double x, double y, double angle=0);


        virtual Rect<int> getRenderBounds() override;

        template<typename T>
        std::shared_ptr<T> getComponent() {
            for(auto& component : this->components) {
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
