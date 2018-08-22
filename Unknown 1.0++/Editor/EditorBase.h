//
// Created by cub3d on 08/08/18.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_EDITORBASE_H
#define UNKNOWN_DEVELOPMENT_TOOL_EDITORBASE_H

#include <SDL.h>
#include "imgui.h"
#include <deque>
#include "../Scene/Scene.h"

namespace Unknown
{
class EditorBase : public ::Unknown::Scene
    {
        std::deque<float> fps;

    public:
        EditorBase();

        virtual void update() override;

        virtual ~EditorBase();
    };
}




#endif //UNKNOWN_DEVELOPMENT_TOOL_EDITORBASE_H
