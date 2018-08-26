//
// Created by cub3d on 08/08/18.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_EDITORBASE_H
#define UNKNOWN_DEVELOPMENT_TOOL_EDITORBASE_H

#include <SDL.h>
#include "imgui.h"
#include <deque>
#include "../Scene/Scene.h"
#include "EntityEditor.h"

namespace Unknown
{
class EditorBase : public ::Unknown::Scene
    {
        std::deque<float> fps;
        std::vector<EntityEditor> entityEditors;
        std::string under;

        std::shared_ptr<Entity> selected;

        bool editing;

    public:
        EditorBase(const std::string &under);

        virtual void update() override;
        virtual void render() const override;

        virtual ~EditorBase();

        std::shared_ptr<::Unknown::Scene> getLastScene() const;

    void createMenuBar();
};
}




#endif //UNKNOWN_DEVELOPMENT_TOOL_EDITORBASE_H
