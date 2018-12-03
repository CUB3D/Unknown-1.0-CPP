//
// Created by cub3d on 06/11/18.
//

#include "FrameBuffer.h"

Unknown::FrameBuffer::FrameBuffer(const Unknown::Dimension<int> frameSize) : frameSize(frameSize) {}

void Unknown::FrameBuffer::bind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, fboID);
}

void Unknown::FrameBuffer::unbind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Unknown::FrameBuffer::createFBO() {
    this->created = true;

    glGenFramebuffers(1, &fboID);
    glBindFramebuffer(GL_FRAMEBUFFER, fboID);

    glGenTextures(1, &textureBufferID);
    glBindTexture(GL_TEXTURE_2D, textureBufferID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frameSize.width, frameSize.height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureBufferID, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenRenderbuffers(1, &rboID);
    glBindRenderbuffer(GL_RENDERBUFFER, rboID);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH32F_STENCIL8, frameSize.width, frameSize.height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rboID);
    glBindBuffer(GL_RENDERBUFFER, 0);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        printf("Invalid framebuffer\n");
    } else {
        printf("Framebuffer valid\n");
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

void Unknown::FrameBuffer::render(const Shader* s) const {
    s->bind();
    glDisable(GL_DEPTH_TEST);
    glBindVertexArray(vaoInfo.vao);
    //s->setFloat("fboTexture", 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureBufferID);
    //bind rbo
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
