//
// Created by cub3d on 06/11/18.
//

#ifndef UNKNOWN_FRAMEBUFFER_H
#define UNKNOWN_FRAMEBUFFER_H


#include "../GL/GL.h"
#include "../Utils.h"

namespace Unknown
{
    class FrameBuffer
    {
        GLuint fboID;
        GLuint textureBufferID;
        GLuint rboID;

        Dimension<int> frameSize;



    public:
        FrameBuffer(const Dimension<int> frameSize);

        void createFBO();

        void bindFBO();
        void renderFBO() const;

    };
}


#endif //UNKNOWN_FRAMEBUFFER_H
