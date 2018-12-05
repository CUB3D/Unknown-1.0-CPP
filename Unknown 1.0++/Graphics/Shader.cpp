//
// Created by cub3d on 25/08/18.
//

#include <cstdio>
#include "Shader.h"

Shader::Shader() : prog(-1) {}

Shader::Shader(const std::string &vertex, const std::string &fragment) : prog(-1), vertexSrc(vertex), fragmentSrc(fragment) {}

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
        printf("Error compiling vertex shader (name: %s): ", getName().c_str());

        int infologLength = 0;
        int charsWritten;

        glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH,&infologLength);

        if (infologLength > 0)
        {
			char* infoLog = (char*)malloc(infologLength * sizeof(char));
            glGetShaderInfoLog(vertShader, infologLength, &charsWritten, infoLog);

            printf("%s\n", infoLog);

			free(infoLog);
            return;
        }
    }

    const GLchar* frag = fragmentSrc.c_str();
    glShaderSource(fragShader, 1, &frag, nullptr);
    glCompileShader(fragShader);

    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &ok);
    if(!ok) {
        printf("Error compiling fragment shader (name: %s): ", getName().c_str());

        int infologLength = 0;
        int charsWritten;

        glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH,&infologLength);

        if (infologLength > 0)
        {
			char* infoLog = (char*)malloc(infologLength * sizeof(char));
            glGetShaderInfoLog(fragShader, infologLength, &charsWritten, infoLog);

            printf("%s\n", infoLog);

			free(infoLog);
            return;
        }

        //If debug
        printf("Shader: \n");
        printf("--------------\n");
        printf("%s\n", frag);
        printf("--------------\n");
        exit(-1);
    }


    prog = glCreateProgram();
    glAttachShader(prog, vertShader);
    glAttachShader(prog, fragShader);

    glLinkProgram(prog);


    glGetProgramiv(prog, GL_LINK_STATUS, &ok);
    if(!ok) {
        printf("Error linking shader (name: %s): ", getName().c_str());

        int infologLength = 0;
        int charsWritten;

        glGetShaderiv(prog, GL_INFO_LOG_LENGTH,&infologLength);

        if (infologLength > 0)
        {
			char* infoLog = (char*)malloc(infologLength * sizeof(char));
            glGetShaderInfoLog(prog, infologLength, &charsWritten, infoLog);

            printf("%s\n", infoLog);

			free(infoLog);
        }
    }


    glValidateProgram(prog);
}

void Shader::bind(bool compile) {
    if(compile && this->prog == -1)
        this->compile();
    glUseProgram(prog);
}

void Shader::bind() const {
    glUseProgram(prog);
}

void Shader::unbind() const {
    glUseProgram(0);
}

void Shader::setVec3(const char *name, const float x, const float y, const float z) {
    glUniform3f(glGetUniformLocation(this->prog, name), x, y, z);
}

void Shader::setFloat(const char *name, const float f) {
    glUniform1f(glGetUniformLocation(this->prog, name), f);
}

std::string Shader::getName() {
    return "RAM";
}

void Shader::setColour(const char *name, const Unknown::Colour &colour) {
    setVec4(name, (float) (colour.red / 255.0), (float) (colour.green / 255.0),
        (float) (colour.blue / 255.0), (float) (colour.alpha / 255.0));
}

void Shader::setVec4(const char *name, const float w, const float x, const float y, const float z) {
    glUniform4f(glGetUniformLocation(this->prog, name), w, x, y, z);
}

void Shader::setInt(const char *name, const int i) {
    glUniform1i(glGetUniformLocation(this->prog, name), i);
}
