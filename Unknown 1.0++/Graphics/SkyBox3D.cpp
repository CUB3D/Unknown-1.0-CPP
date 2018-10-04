//
// Created by cub3d on 04/10/18.
//

#include "SkyBox3D.h"
#include "FileShader.h"

void SkyBox3D::render(RenderingPipeline3D& pipeline) {
    glDepthMask(GL_FALSE);
    glDepthFunc(GL_LEQUAL);
    sky.bind(true);
    sky.setFloat("skybox", 0);
    glUniformMatrix4fv(glGetUniformLocation(sky.prog, "proj"), 1, GL_FALSE, &pipeline.projectionMatrix[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(sky.prog, "view"), 1, GL_FALSE, &glm::mat4(glm::mat3(pipeline.getCamera().getViewMatrix()))[0][0]);
    glBindVertexArray(vao);
    glBindTexture(GL_TEXTURE_CUBE_MAP, (GLuint)skyboxTexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDepthMask(GL_TRUE);
}

void SkyBox3D::init() {
    float skyboxVertices[] = {
            // positions
            -1.0f,  1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            -1.0f,  1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f,  1.0f
    };

    GLuint cubeMapVBO;

    glGenBuffers(1, &cubeMapVBO);

    // Bind VBO and put data in it
    glBindBuffer(GL_ARRAY_BUFFER, cubeMapVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &vao);

    // Bind the VAO and fill in the locations of each piece of vertex data
    glBindVertexArray(vao);

    // Verticies
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLuint SkyBox3D::loadCubeMap(std::vector<std::string>& faces) {
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    for(int i = 0; i < faces.size(); i++) {
        printf("Loading %s\n", faces[i].c_str());

        SDL_Surface* imageSurface = IMG_Load(faces[i].c_str());

        if (!imageSurface) {
            printf("Error: failed to load image, %s\n", IMG_GetError());
            return 0;
        }

        int nOfColors = imageSurface->format->BytesPerPixel;
        int mode = GL_RGBA;
        if( nOfColors == 4 )     // contains an alpha channel
        {
            if(imageSurface->format->Rmask == 0x000000ff) {
                mode = GL_RGBA;
            } else {
                mode = GL_BGRA;
            }
        } else if( nOfColors == 3 ) {
            if(imageSurface->format->Rmask == 0x000000ff) {
                mode = GL_RGB;
            } else {
                mode = GL_BGR;
            }
        }

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, imageSurface->w, imageSurface->h, 0, mode, GL_UNSIGNED_BYTE, imageSurface->pixels);

        SDL_FreeSurface(imageSurface);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}

SkyBox3D::SkyBox3D(std::vector<std::string> textures) : sky(FileShader("Sky_vert.glsl", "Sky_frag.glsl")) {
    this->skyboxTexture = loadCubeMap(textures);
}
