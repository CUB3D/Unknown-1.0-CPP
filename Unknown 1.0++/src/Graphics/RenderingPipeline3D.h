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
#include "RenderingBackend.h"
#include "SkyBox3D.h"
#include "light/LightingManager2D.h"


class MeshRenderer;
class SkyBox3D;

class RenderingPipeline3D
{
    Shader s;
    Camera3D camera;

    //std::array<struct PointLight, 10> pointLights;
    //std::array<struct DirectionalLight, 10> directionalLights;

//    std::array<float, ((3+3+3+3)*32 + (3+3+3+3+1+1+1)*32 + (3+3+3+3+3+1)*32) * sizeof(float)> lightBuffer;

    LightingManager2D lm;

    Shader fboS;
    GLuint fbo;
    GLuint texBuffer;
    Unknown::VertexInfo fbov;
    GLuint rbo;

    GLuint lightUBO;

public:
    glm::mat4 projectionMatrix;

    //TODO: move
    SkyBox3D* skybox;

    RenderingPipeline3D();
    void init();

    std::vector<std::shared_ptr<MeshRenderer>> meshes;

    void render();

    Camera3D& getCamera();
};


#endif //UNKNOWN_DEVELOPMENT_TOOL_RENDERINGPIPELINE3D_H
