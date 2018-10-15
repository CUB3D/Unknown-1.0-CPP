//
// Created by cub3d on 02/10/18.
//

#include <cstdio>
#include "Mesh.h"

void Mesh::loadVBO() {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(unsigned int), &indicies[0], GL_STATIC_DRAW);

    int tmp = 3;

    if(normals.size() > 0)
        tmp += 3;

    if(uvs.size() > 0)
        tmp += 2;

    int SIZE = verticies.size() * (tmp);

    GLfloat* data = (GLfloat*) malloc(SIZE * sizeof(GLfloat));

    int x = 0;

    for(int i = 0; i < verticies.size(); i++) {
        auto &v = verticies[i];

        data[x++] = v.x;
        data[x++] = v.y;
        data[x++] = v.z;

        if(normals.size() > 0) {
            auto& n = normals[i];
            data[x++] = n.x;
            data[x++] = n.y;
            data[x++] = n.z;
        }

        if(uvs.size() > 0) {
            auto& uv = uvs[i];
            data[x++] = uv.x;
            data[x++] = uv.y;
        }
    }

    glBufferData(GL_ARRAY_BUFFER, SIZE * sizeof(GLfloat), data, GL_STATIC_DRAW);

    int stride = (tmp) * sizeof(GLfloat);

    int tmp2 = 3;

    // Verticies
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, 0);

    if(normals.size() > 0) {
        // Normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride,
                              reinterpret_cast<const void *>(tmp2 * sizeof(GLfloat)));
        tmp2 += 3;
    }

    if(uvs.size() > 0) {
        // UV's
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride,
                              reinterpret_cast<const void *>(tmp2 * sizeof(GLfloat)));
        tmp2 += 2;
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Mesh::render() {
    glBindVertexArray(vao);

    // Diffuse map
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, (GLuint) diffuseMaps[0].pointer);

    glActiveTexture(GL_TEXTURE1);
    if(specularMaps.size() > 0) {
        // Specular map
        glBindTexture(GL_TEXTURE_2D, (GLuint) specularMaps[0].pointer);
    } else {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    glDrawElements(GL_TRIANGLES, verticies.size(), GL_UNSIGNED_INT, 0);
    //glBindVertexArray(0);
}