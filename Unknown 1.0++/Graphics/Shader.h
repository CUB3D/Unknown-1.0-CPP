//
// Created by cub3d on 25/08/18.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_SHADER_H
#define UNKNOWN_DEVELOPMENT_TOOL_SHADER_H

#include <string>

class Shader
{
public:
    int prog;
    std::string vertexSrc;
    std::string fragmentSrc;

    Shader();
    Shader(const std::string& vertex, const std::string& fragment);

    void compile();

    void bind() const;
    void unbind() const;
};


#endif //UNKNOWN_DEVELOPMENT_TOOL_SHADER_H
