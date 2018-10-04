//
// Created by cub3d on 03/10/18.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_RENDERINGPIPELINE3D_H
#define UNKNOWN_DEVELOPMENT_TOOL_RENDERINGPIPELINE3D_H

#include "../Model/MeshRenderer.h"
#include "Shader.h"
#include <memory>
#include "Camera3D.h"

class MeshRenderer;

class RenderingPipeline3D
{
    Shader s;
    Camera3D camera;


public:
    glm::mat4 projectionMatrix;

    RenderingPipeline3D();

    std::vector<std::shared_ptr<MeshRenderer>> meshes;

    void render();

    Camera3D& getCamera();
};


#endif //UNKNOWN_DEVELOPMENT_TOOL_RENDERINGPIPELINE3D_H
