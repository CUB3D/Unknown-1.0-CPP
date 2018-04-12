//
// Created by cub3d on 03/04/18.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_DEBUGSCENE_H
#define UNKNOWN_DEVELOPMENT_TOOL_DEBUGSCENE_H

#include "Scene.h"
#include "../Font.h"

namespace Unknown
{
    class DebugScene : public MenuScene
    {
    public:
        std::shared_ptr<Graphics::Font> font;

        DebugScene(const std::string name, std::shared_ptr<Graphics::Font> font);
        virtual void update() override;
        virtual void render() const override;

        virtual ~DebugScene();

    };
}


#endif //UNKNOWN_DEVELOPMENT_TOOL_DEBUGSCENE_H
