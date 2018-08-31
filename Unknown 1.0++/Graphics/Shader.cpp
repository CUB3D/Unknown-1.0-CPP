//
// Created by cub3d on 25/08/18.
//

#include <cstdio>
#include "Shader.h"

#include "../GL/GL.h"

void Shader::bind() const {
    glUseProgram(prog);
}

void Shader::unbind() const {
    glUseProgram(0);
}

void Shader::compile() {
    // Create shaders
    int vertShader = glCreateShader(GL_VERTEX_SHADER);
    int fragShader = glCreateShader(GL_FRAGMENT_SHADER);

    GLint ok = GL_FALSE;

    // todo: is null strlen shader
    const GLchar* vert = vertexSrc.c_str();
    glShaderSource(vertShader, 1, &vert, nullptr);
    glCompileShader(vertShader);

    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &ok);
    if(!ok) {
        printf("Error compiling vertex shader: ");

        int infologLength = 0;
        int charsWritten;

        glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH,&infologLength);

        if (infologLength > 0)
        {
            char infoLog[infologLength];
            glGetShaderInfoLog(vertShader, infologLength, &charsWritten, infoLog);

            printf("%s\n", infoLog);
            return;
        }
    }

    const GLchar* frag = fragmentSrc.c_str();
    glShaderSource(fragShader, 1, &frag, nullptr);
    glCompileShader(fragShader);

    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &ok);
    if(!ok) {
        printf("Error compiling fragment shader: ");

        int infologLength = 0;
        int charsWritten;

        glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH,&infologLength);

        if (infologLength > 0)
        {
            char infoLog[infologLength];
            glGetShaderInfoLog(fragShader, infologLength, &charsWritten, infoLog);

            printf("%s\n", infoLog);
            return;
        }
    }


    prog = glCreateProgram();
    glAttachShader(prog, vertShader);
    glAttachShader(prog, fragShader);

    glLinkProgram(prog);


    glGetProgramiv(prog, GL_LINK_STATUS, &ok);
    if(!ok) {
        printf("Error linking shader: ");

        int infologLength = 0;
        int charsWritten;

        glGetShaderiv(prog, GL_INFO_LOG_LENGTH,&infologLength);

        if (infologLength > 0)
        {
            char infoLog[infologLength];
            glGetShaderInfoLog(prog, infologLength, &charsWritten, infoLog);

            printf("%s\n", infoLog);
        }
    }


    glValidateProgram(prog);

}

Shader::Shader() : prog(-1) {}

Shader::Shader(const std::string &vertex, const std::string &fragment) : prog(-1), vertexSrc(vertex), fragmentSrc(fragment) {}
