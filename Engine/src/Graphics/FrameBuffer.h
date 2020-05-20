//
// Created by cub3d on 06/11/18.
//

#ifndef UNKNOWN_FRAMEBUFFER_H
#define UNKNOWN_FRAMEBUFFER_H


#include <GL/GL.h>
#include <Utils.h>
#include <Types/Dimension.h>
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

        Dimension<int> frameSize;

        FrameBuffer(const Dimension<int> frameSize);

        void createFBO();

        void bind() const;
        void unbind() const;
        void render(const Shader& s) const;

    };
}


#endif //UNKNOWN_FRAMEBUFFER_H
