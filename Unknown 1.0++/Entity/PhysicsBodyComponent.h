//int
// Created by cub3d on 29/07/2018.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_PHYSICSBODYCOMPONENT_H
#define UNKNOWN_DEVELOPMENT_TOOL_PHYSICSBODYCOMPONENT_H

#include "Component.h"
#include <Box2D/Box2D.h>
#include "../Scene/Scene.h"
#include "Types/Vector.h"
#include "../IInitable.h"

namespace Unknown
{
    class PhysicsBodyComponent : public Component, public IInitable<Scene&, std::shared_ptr<Entity>>
    {
        //TODO: no
    public:
        b2BodyDef bodyDefinition;
        b2Body* body;

        b2FixtureDef fixtureDefinition;
        b2Fixture* fixture;

        b2PolygonShape polygon;
        b2CircleShape circle;

        b2Shape::Type bodyShape;


        Point<double> maxSpeed;
        Vector lastForce;

        //public:
        PhysicsBodyComponent();
        PhysicsBodyComponent(std::shared_ptr<Entity> ent);

        //TODO: attach method

        virtual void init(Scene& scene, std::shared_ptr<Entity> ent) override;

        virtual void update(Entity &ent) override;
        virtual void onDisable(Entity& ent) override;


        void applyForce(const Vector& vec);

        Vector getXDirection() const;
    };
}


#endif //UNKNOWN_DEVELOPMENT_TOOL_PHYSICSBODYCOMPONENT_H
