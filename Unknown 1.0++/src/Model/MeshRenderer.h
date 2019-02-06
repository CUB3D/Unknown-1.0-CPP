//
// Created by cub3d on 03/10/18.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_MESHRENDERER_H
#define UNKNOWN_DEVELOPMENT_TOOL_MESHRENDERER_H

#include "MeshContainer.h"
#include "Graphics/Shader.h"
#include "Graphics/RenderingPipeline3D.h"

class RenderingPipeline3D;

class MeshRenderer
{
protected:
    MeshContainer meshes;

public:
    MeshRenderer(MeshContainer& mesh);

    virtual void render(Shader &shad, RenderingPipeline3D &renderPipeline) = 0;
};


#endif //UNKNOWN_DEVELOPMENT_TOOL_MESHRENDERER_H
