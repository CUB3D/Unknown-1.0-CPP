//
// Created by cub3d on 03/10/18.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_RENDERINGPIPELINE3D_H
#define UNKNOWN_DEVELOPMENT_TOOL_RENDERINGPIPELINE3D_H

#include "../Model/MeshRenderer.h"
#include "Shader.h"
#include <memory>

class MeshRenderer;

class RenderingPipeline3D
{
    Shader s;

public:
    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix;

    RenderingPipeline3D();

    std::vector<std::shared_ptr<MeshRenderer>> meshes;

    void render();
};


#endif //UNKNOWN_DEVELOPMENT_TOOL_RENDERINGPIPELINE3D_H
