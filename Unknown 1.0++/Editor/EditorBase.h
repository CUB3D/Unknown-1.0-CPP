//
// Created by cub3d on 08/08/18.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_EDITORBASE_H
#define UNKNOWN_DEVELOPMENT_TOOL_EDITORBASE_H

#include <SDL2/SDL.h>
#include "imgui.h"
#include <deque>

namespace Unknown
{
    class EditorBase
    {
        std::deque<float> fps;

    public:
        EditorBase();

        void update();

        virtual ~EditorBase();
    };

    EditorBase& getEditor() {
        static EditorBase base;
        return base;
    }
}




#endif //UNKNOWN_DEVELOPMENT_TOOL_EDITORBASE_H
