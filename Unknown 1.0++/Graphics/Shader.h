//
// Created by cub3d on 25/08/18.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_SHADER_H
#define UNKNOWN_DEVELOPMENT_TOOL_SHADER_H

#include <string>
#include <Types/Colour.h>
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

    virtual std::string getName();

    //TODO: const
    void setVec3(const char* name, const float x, const float y, const float z);
    void setVec4(const char* name, const float w, const float x, const float y, const float z);
    void setMat4(const char* name, const glm::mat4& mat);
    void setInt(const char* name, const int i);
    void setFloat(const char* name, const float f);
    void setColour(const char* name, const Unknown::Colour& colour);
};


#endif //UNKNOWN_DEVELOPMENT_TOOL_SHADER_H
