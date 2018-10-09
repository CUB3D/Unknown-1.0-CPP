//
// Created by cub3d on 04/10/18.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_SKYBOX3D_H
#define UNKNOWN_DEVELOPMENT_TOOL_SKYBOX3D_H

#include "RenderingBackend.h"
#include "Shader.h"
#include "RenderingPipeline3D.h"

class RenderingPipeline3D;

class SkyBox3D {
    GLuint vao;
    GLuint skyboxTexture;
    Shader sky;

public:
    SkyBox3D(std::vector<std::string> textures);

    void init();

    void render(RenderingPipeline3D& pipeline);
    GLuint loadCubeMap(std::vector<std::string>& faces);
};


#endif //UNKNOWN_DEVELOPMENT_TOOL_SKYBOX3D_H
