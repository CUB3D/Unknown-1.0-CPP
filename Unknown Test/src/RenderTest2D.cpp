//
// Created by cub3d on 31/10/18.
//

#include "RenderTest2D.h"
#include <Tracy.hpp>
#include <TracyOpenGL.hpp>
#include <light/PointLight.h>

class LightingManager {
public:
    static constexpr int BUFFER_CAPACITY = 2;
    static constexpr int POINT_SIZE = BUFFER_CAPACITY * PointLight::BUFFER_SIZE;

    float* lightBuffer;

    std::vector<std::shared_ptr<PointLight>> lights;

    GLuint lightUBO {0};

    LightingManager() {
        lightBuffer = static_cast<float *>(malloc(POINT_SIZE * sizeof(float)));

        for(int i = 0; i < POINT_SIZE; i++) {
            lightBuffer[i] = 0;
        }
    }

    void init() {
        glGenBuffers(1, &lightUBO);
        glBindBuffer(GL_UNIFORM_BUFFER, lightUBO);
        glBufferData(GL_UNIFORM_BUFFER, POINT_SIZE, &lightBuffer[0], GL_DYNAMIC_DRAW);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

    void updateBuffer() {
        ZoneScopedN("R2D::buffer bind");
        glBindBuffer(GL_UNIFORM_BUFFER, lightUBO);
        void* map = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
        memcpy(map, &lightBuffer[0], POINT_SIZE * sizeof(float));
        glUnmapBuffer(GL_UNIFORM_BUFFER);
    }

    void updateLightBuffer() {
        ZoneScopedN("R2D::light to buffer");
        for (int i = 0; i < lights.size(); i++) {
            lights[i]->show_edit(i);
            lights[i]->toBuffer(&lightBuffer[i * POINT_SIZE]);
        }

        if(ImGui::Begin("Light buffer")) {
            ImGui::Columns(4, "Buffer", true);
            for(int i = 0; i < 4; i++) {
                for (int j = 0; j < POINT_SIZE / 4; j++) {
                    ImGui::Text("%f", lightBuffer[j * 4 + i]);
                }
                ImGui::NextColumn();
            }
            ImGui::NextColumn();
        }
        ImGui::End();
    }

    void bindBuffer(int index) {
        glBindBufferBase(GL_UNIFORM_BUFFER, index, lightUBO);
    }
};

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

RenderTest2D::RenderTest2D() : Scene() {}


FileShader s("2DVert.glsl", "2DFrag.glsl");
Unknown::VertexInfo verticies;
Unknown::TextureInfo texture;
Unknown::TextureInfo spec;




void RenderTest2D::render() const {
    ZoneScopedN("R2D::render");
    TracyGpuZone("Render");

    static auto p1 = std::make_shared<PointLight>(glm::vec3(0.5, 0.5, 0), 0.2, 0.1, 0.4, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), true);
    static LightingManager lm;


    if(s.prog == -1) {
        ZoneNamedN(level2, "R2D::Setup", true);
        TracyGpuZone("Setup");

        texture = Unknown::getRendererBackend()->loadTexture("crate.png");
        spec = Unknown::getRendererBackend()->loadTexture("crate_spec.png");
        verticies = Unknown::getRendererBackend()->createRectVerticies(0, 0, 1, 1);
        s.compile();

        lm.init();


//        lm.lights.emplace_back();
        lm.lights.push_back(p1);

        lm.updateBuffer();
    }

    s.bind();

    static Camera2D camera(texture.width, texture.height);

//    auto& uk = Unknown::getUnknown();
//
//    float centerX = texture.width / 2.0f;
//    float centerY = texture.height / 2.0f;
//
//    // Create the ortagonal projection
//    glm::mat4 projection = glm::ortho(0.0f, 1.0f, 1.0f, 0.0f, -100.0f, 0.0f);
//
//    // Create the view matrix
//    glm::mat4 view = glm::mat4(1.0f);
//
//    // Create the model matrix
//    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0 + centerX, 0 + centerY, 0.5f));
//    model = glm::rotate(model, (float) glm::radians(0.0f), glm::vec3(0, 0, 1.0f));
//
//    model = glm::translate(model, glm::vec3(-centerX, -centerY, 0.0f));
//
//    // Projection * view * model
//    glm::mat4 mvp = projection * view * model;

    int mx, my;
    SDL_GetMouseState(&mx, &my);
    glm::vec3 tmp = camera.mvp * glm::vec4(mx/1024.0, my/1024.0, 0.0f, 1.0f);
    p1->position = glm::vec3(tmp.x, tmp.y, 0);

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

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, (GLuint)texture.pointer);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, (GLuint) spec.pointer);

    glBindVertexArray(verticies.vao);

    // Render data
    glDrawArrays(GL_TRIANGLES, 0, verticies.vertexCount);

    // Unbind stuff
   // glBindVertexArray(0);
   // s.unbind();
}

