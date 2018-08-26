//
// Created by cub3d on 25/08/18.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_GL_H
#define UNKNOWN_DEVELOPMENT_TOOL_GL_H


#ifdef __EMSCRIPTEN__
    #include <GLFW/glfw3.h>
    #include "GLES3/gl3.h"
#else
    // On most platforms, glad is all you need
    #include "glad/glad.h"
#endif

namespace Unknown {
    void initGL();
}

#endif //UNKNOWN_DEVELOPMENT_TOOL_GL_H
