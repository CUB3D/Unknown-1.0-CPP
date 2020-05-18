//
// Created by cub3d on 06/11/18.
//

#include "FrameBuffer.h"
#include <Tracy.hpp>
#include <TracyOpenGL.hpp>
#include "core/log/Log.h"

Unknown::FrameBuffer::FrameBuffer(const Unknown::Dimension<int> frameSize) : frameSize(frameSize) {}

void Unknown::FrameBuffer::bind() const {
    ZoneScopedN("FBO::bind");
    TracyGpuZone("FBO::bind");
    glBindFramebuffer(GL_FRAMEBUFFER, fboID);
}

void Unknown::FrameBuffer::unbind() const {
    ZoneScopedN("FBO::unbind");
    TracyGpuZone("FBO::unbind");
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Unknown::FrameBuffer::createFBO() {
    ZoneScopedN("FBO::CreateFBO");
    TracyGpuZone("FBO::CreateFBO");
    this->created = true;

    //TODO: config samples, optional MSAA, optional postprocessing off
    constexpr int samples = 16;

    glGenFramebuffers(1, &fboID);
    glBindFramebuffer(GL_FRAMEBUFFER, fboID);

    glGenTextures(1, &textureBufferID);

    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, textureBufferID);
    glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, GL_RGB, frameSize.width, frameSize.height, GL_TRUE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, textureBufferID, 0);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);

    glGenRenderbuffers(1, &rboID);
    glBindRenderbuffer(GL_RENDERBUFFER, rboID);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, GL_DEPTH32F_STENCIL8, frameSize.width, frameSize.height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rboID);
    glBindBuffer(GL_RENDERBUFFER, 0);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        UK_INFO("Invalid framebuffer\n");
    } else {
        UK_INFO("Framebuffer valid\n");
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);




    glGenFramebuffers(1, &fbo2ID);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo2ID);

    glGenTextures(1, &texBuffer2);
    glBindTexture(GL_TEXTURE_2D, texBuffer2);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frameSize.width, frameSize.height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texBuffer2, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        UK_INFO("Invalid framebuffer2\n");
    } else {
        UK_INFO("Framebuffer2 valid\n");
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    constexpr const int SIZE = (2 + 2) * 6;

    float data[SIZE] = {
        -1, 1,
        0, 1,

        -1, -1,
        0, 0,

        1, -1,
        1, 0,


        -1, 1,
        0, 1,

        1, -1,
        1, 0,

        1, 1,
        1, 1

    };

    glGenBuffers(1, &vaoInfo.vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vaoInfo.vbo);
    glBufferData(GL_ARRAY_BUFFER, SIZE*sizeof(GLfloat), data, GL_STATIC_DRAW);

    glGenVertexArrays(1, &vaoInfo.vao);
    glBindVertexArray(vaoInfo.vao);

    constexpr const int STRIDE = (2 + 2) * sizeof(GLfloat);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, STRIDE, nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, STRIDE, reinterpret_cast<const void *>(2 * sizeof(GLfloat)));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Unknown::FrameBuffer::render(const Shader& s) const {
    ZoneScopedN("FBO::Render");
    TracyGpuZone("FBO::Render");

    glBindFramebuffer(GL_READ_FRAMEBUFFER, fboID);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo2ID);
    glBlitFramebuffer(0, 0, frameSize.width, frameSize.height, 0, 0, frameSize.width, frameSize.height, GL_COLOR_BUFFER_BIT, GL_NEAREST);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    s.bind();
    glDisable(GL_DEPTH_TEST);
    glBindVertexArray(vaoInfo.vao);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texBuffer2);

    glDrawArrays(GL_TRIANGLES, 0, 6);
}
