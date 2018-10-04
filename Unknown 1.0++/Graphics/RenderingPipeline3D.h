//
// Created by cub3d on 03/10/18.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_RENDERINGPIPELINE3D_H
#define UNKNOWN_DEVELOPMENT_TOOL_RENDERINGPIPELINE3D_H

#include "../Model/MeshRenderer.h"
#include "Shader.h"
#include <memory>
#include "Camera3D.h"
#include <array>

struct DirectionalLight {
    glm::vec3 direction;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

struct PointLight {
    glm::vec3 position;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    float constant;
    float linear;
    float quadratic;
};


class MeshRenderer;

class RenderingPipeline3D
{
    Shader s;
    Camera3D camera;

    std::array<struct PointLight, 10> pointLights;
    std::array<struct DirectionalLight, 10> directionalLights;


public:
    glm::mat4 projectionMatrix;

    RenderingPipeline3D();

    std::vector<std::shared_ptr<MeshRenderer>> meshes;

    void render();

    Camera3D& getCamera();
};


#endif //UNKNOWN_DEVELOPMENT_TOOL_RENDERINGPIPELINE3D_H
