//
// Created by cub3d on 29/07/2018.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_PHYSICSBODYCOMPONENT_H
#define UNKNOWN_DEVELOPMENT_TOOL_PHYSICSBODYCOMPONENT_H

#include "Component.h"
#include "Box2D/Box2D.h"
#include "../Scene/Scene.h"

namespace Unknown
{
    class PhysicsBodyComponent : public Component
    {
        //TODO: no
    public:
        b2BodyDef bodyDefinition;
        b2Body* body;
        b2PolygonShape shape;
        b2FixtureDef fixtureDefinition;

        //public:
        PhysicsBodyComponent(std::shared_ptr<Entity> ent, Scene *scene, b2BodyType type);

        virtual void update(Entity &ent) override;
    };
}


#endif //UNKNOWN_DEVELOPMENT_TOOL_PHYSICSBODYCOMPONENT_H