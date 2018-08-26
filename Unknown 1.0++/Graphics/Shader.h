//
// Created by cub3d on 25/08/18.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_SHADER_H
#define UNKNOWN_DEVELOPMENT_TOOL_SHADER_H


class Shader
{
public:
    int prog;

    Shader();

    void compile();

    void bind();
    void unbind();
};


#endif //UNKNOWN_DEVELOPMENT_TOOL_SHADER_H
