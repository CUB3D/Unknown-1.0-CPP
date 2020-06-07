//
// Created by cub3d on 06/11/18.
//

#ifndef UNKNOWN_FRAMEBUFFER_H
#define UNKNOWN_FRAMEBUFFER_H


#include <GL/GL.h>
#include <Utils.h>
#include "RenderingBackend.h"
#include "Shader.h"

namespace Unknown
{
    class FrameBuffer
    {
        GLuint fboID;
        GLuint textureBufferID;
        GLuint rboID;
        VertexInfo vaoInfo;

        GLuint fbo2ID;
        GLuint texBuffer2;

        bool created;
    public:

        glm::vec2 frameSize;

        FrameBuffer(const glm::vec2 frameSize);

        void createFBO();

        void bind() const;
        void unbind() const;
        void render(const Shader& s) const;

    };
}


#endif //UNKNOWN_FRAMEBUFFER_H
