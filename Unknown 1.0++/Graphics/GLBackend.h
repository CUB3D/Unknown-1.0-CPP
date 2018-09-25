//
// Created by cub3d on 26/08/18.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_GLBACKEND_H
#define UNKNOWN_DEVELOPMENT_TOOL_GLBACKEND_H

#include "RenderingBackend.h"
#include "FileShader.h"
#include "../GL/GL.h"
#include <map>

namespace Unknown
{
    const static std::string imageVertexShader = "#version 300 es\n"
                                                 "\n"
                                                 "precision highp float;\n"
                                                 "\n"
                                                 "layout(location = 0) in vec3 inVertex; // Input in model space\n"
                                                 "layout(location = 1) in vec4 inColour;\n"
                                                 "layout(location = 2) in vec2 vertexUV; // Input tex coord for this vertex\n"
                                                 "layout(location = 3) in vec3 inVertexNormal; // The normal for this vertex\n"
                                                 "\n"
                                                 "out vec2 UV;\n"
                                                 "out vec3 vertexNormal;\n"
                                                 "\n"
                                                 "uniform mat4 MVP; // The modelview matrix\n"
                                                 "\n"
                                                 "void main() {\n"
                                                 "    UV = vertexUV;\n"
                                                 "    vertexNormal = inVertexNormal;\n"
                                                 "\n"
                                                 "    gl_Position = MVP * vec4(inVertex, 1.0);\n"
                                                 "}";

    const static std::string imageFragmentShader = "#version 300 es\n"
                                                   "\n"
                                                   "precision highp float;\n"
                                                   "\n"
                                                   "uniform sampler2D texture0;\n"
                                                   "\n"
                                                   "in vec2 UV;\n"
                                                   "in vec3 vertexNormal;\n"
                                                   "\n"
                                                   "out vec4 fragColour;\n"
                                                   "\n"
                                                   "void main() {\n"
                                                   "    vec3 lightColour = vec3(1, 1, 1);\n"
                                                   "\n"
                                                   "    float ambientLightStrength = 1.0;\n"
                                                   "    vec3 ambient = ambientLightStrength * lightColour;\n"
                                                   "\n"
                                                   "    fragColour = texture(texture0, UV) * vec4(ambient, 1.0);\n"
                                                   "}";

    const static std::string renderingVertexShader = "#version 300 es\n"
                                                     "\n"
                                                     "precision highp float;\n"
                                                     "in vec4 inVertex;\n"
                                                     "uniform mat4 projmat;\n"
                                                     "\n"
                                                     "void main() {\n"
                                                     "    gl_Position = projmat * inVertex;\n"
                                                     "}";

    const static std::string renderingFragmentShader = "#version 300 es\n"
                                                       "\n"
                                                       "precision highp float;\n"
                                                       "\n"
                                                       "uniform vec4 inputColour;\n"
                                                       "\n"
                                                       "out vec4 fragColour;\n"
                                                       "\n"
                                                       "void main() {\n"
                                                       "    fragColour = inputColour;\n"
                                                       "}";


    class GLBackend : public RenderingBackend
    {
        Shader basicRenderer;
        Shader textureRenderer;

    public:
        GLBackend();

        virtual void drawRect(const int x, const int y, const int width, const int height, const double angle, const Colour &colour) override;
        virtual void drawPoint(const int x, const int y, const Colour& colour) override;
        virtual void drawLine(const int sx, const int sy, const int ex, const int ey, const Colour &col) override;
        virtual void drawCircle(const int cx, const int cy, const int radius, const Colour &col) override;

        virtual TextureInfo loadTexture(std::string &path) override;
        virtual VertexInfo createRectVerticies(const int x, const int y, const int w, const int h) override;
        virtual void renderTexture(const int x, const int y, const double angle, const TextureInfo &texture, const VertexInfo &verticies)  override;
        virtual void renderQuad(const int x, const int y, const double angle, const VertexInfo& verts, Shader& shader);

        virtual void clearScreen();

        TextureInfo createFontTexture(TTF_Font &font, const char *str, const Colour &col);
    };
}


#endif //UNKNOWN_DEVELOPMENT_TOOL_GLBACKEND_H
