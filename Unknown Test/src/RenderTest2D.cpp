//
// Created by cub3d on 31/10/18.
//

#include "RenderTest2D.h"
#include <Tracy.hpp>
#include <TracyOpenGL.hpp>
#include <light/PointLight.h>
#include <light/LightingManager2D.h>


class Camera2D {
public:
    glm::mat4 projection {};

    glm::mat4 view {};

    glm::mat4 model {};

    glm::mat4 mvp {};

    Camera2D(float xx, float yy) {

        printf("xx: %f, yy: %f\n", xx, yy);
        // Create the ortagonal projection
        projection = glm::ortho(0.0f, 1.0f, 1.0f, 0.0f, -100.0f, 0.0f);

        // Create the view matrix
        view = glm::mat4(1.0f);

        float x = 0;
        float y = 0;
        double angle = 0;

        float centerX = xx / 2.0f;
        float centerY = yy / 2.0f;

        // Create the model matrix
        model = glm::translate(glm::mat4(1.0f), glm::vec3(x + centerX, y + centerY, 0.5f));
        model = glm::rotate(model, (float) glm::radians(angle), glm::vec3(0, 0, 1.0f));

        model = glm::translate(model, glm::vec3(-centerX, -centerY, 0.0f));

        // Projection * view * model
        mvp = projection * view * model;
    }
};

class Renderable2D {
public:
    Unknown::VertexInfo verticies;
    Unknown::TextureInfo texture;
    Unknown::TextureInfo specularMap;

    Renderable2D(std::string textureName, std::string specularMapName) {
        texture = Unknown::getRendererBackend()->loadTexture(textureName);
        specularMap = Unknown::getRendererBackend()->loadTexture(specularMapName);
        verticies = Unknown::getRendererBackend()->createRectVerticies(0, 0, 1, 1);
    }

    void render() {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, (GLuint)texture.pointer);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, (GLuint) specularMap.pointer);

        glBindVertexArray(verticies.vao);

        // Render data
        glDrawArrays(GL_TRIANGLES, 0, verticies.vertexCount);


        // Unbind stuff
         glBindVertexArray(0);
    }
};

class RenderPipeline2D {
public:
    LightingManager2D lm;
    Camera2D camera {2, 2};
    FileShader s {"2DVert.glsl", "2DFrag.glsl"};

    std::vector<Renderable2D> renderables;


    void init() {
        ZoneNamedN(level2, "R2D::Setup", true);
        TracyGpuZone("Setup");
        lm.init();
        s.compile();
    }

    void render() {
        s.bind();

        lm.updateLightBuffer();
        lm.updateBuffer();

        glUniformMatrix4fv(glGetUniformLocation(s.prog, "MVP"), 1, GL_FALSE, &camera.mvp[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(s.prog, "modelMatrix"), 1, GL_FALSE, &camera.mvp[0][0]);
        glUniform1i(glGetUniformLocation(s.prog, "mat.diffuse"), 0);
        glUniform1i(glGetUniformLocation(s.prog, "mat.specular"), 1);
        //TODO: controllable
        s.setFloat("mat.shine", 0.3);

        GLuint lightBlockIndex = glGetUniformBlockIndex(s.prog, "lighting");
        lm.bindBuffer(0);
        glUniformBlockBinding(s.prog, lightBlockIndex, 0);

        for(auto&& r : renderables) {
            r.render();
        }

        s.unbind();
    }
};

RenderTest2D::RenderTest2D() : Scene() {}



void RenderTest2D::render() const {
    ZoneScopedN("R2D::render");
    TracyGpuZone("Render");

    static auto p1 = std::make_shared<PointLight>(glm::vec3(0.5, 0.5, 0), 0.2, 0.1, 0.4, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), true);

    static RenderPipeline2D pipe;

    if(pipe.s.prog == -1) {
        pipe.lm.lights.push_back(p1);
        pipe.renderables.emplace_back("crate.png", "crate_spec.png");

        pipe.init();
    }


    int mx, my;
    SDL_GetMouseState(&mx, &my);
    glm::vec3 tmp = pipe.camera.mvp * glm::vec4(mx/1024.0, my/1024.0, 0.0f, 1.0f);
    p1->position = glm::vec3(tmp.x, tmp.y, 0);

    pipe.render();
}

