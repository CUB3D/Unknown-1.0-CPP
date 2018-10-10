//
// Created by cub3d on 02/10/18.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_MESH_H
#define UNKNOWN_DEVELOPMENT_TOOL_MESH_H

#include <vector>
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include "../GL/GL.h"
#include "../Graphics/RenderingBackend.h"

class Mesh {
public:
    std::vector<glm::vec3> verticies;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> uvs;
    std::vector<unsigned int> indicies;

    std::vector<Unknown::TextureInfo> diffuseMaps;
    std::vector<Unknown::TextureInfo> specularMaps;

    GLuint vbo = 0;
    GLuint vao = 0;
    GLuint ebo = 0;

    void loadVBO();

    void render();
};


#endif //UNKNOWN_DEVELOPMENT_TOOL_MESH_H
