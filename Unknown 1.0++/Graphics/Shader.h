//
// Created by cub3d on 25/08/18.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_SHADER_H
#define UNKNOWN_DEVELOPMENT_TOOL_SHADER_H

#include <string>
#include "../GL/GL.h"

class Shader
{
public:
    GLuint prog;
    std::string vertexSrc;
    std::string fragmentSrc;

    Shader();
    Shader(const std::string& vertex, const std::string& fragment);

    void compile();

    // Same as bind(bool) except will never attempt to compile on bind
    void bind() const;
    void bind(bool compile=true);
    void unbind() const;

    void setVec3(const char* name, float x, float y, float z);
    void setFloat(const char* name, float f);
};


#endif //UNKNOWN_DEVELOPMENT_TOOL_SHADER_H
