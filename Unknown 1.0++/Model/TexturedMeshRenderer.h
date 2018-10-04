//
// Created by cub3d on 03/10/18.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_TEXTUREDMESHRENDERER_H
#define UNKNOWN_DEVELOPMENT_TOOL_TEXTUREDMESHRENDERER_H

#include "MeshRenderer.h"
#include "../Graphics/Shader.h"
#include "../Graphics/RenderingPipeline3D.h"

class TexturedMeshRenderer : public MeshRenderer
{
public:
    TexturedMeshRenderer(MeshContainer& container);

    virtual void render(Shader &shad, RenderingPipeline3D &renderPipeline) override;
};


#endif //UNKNOWN_DEVELOPMENT_TOOL_TEXTUREDMESHRENDERER_H
