//
// Created by cub3d on 31/10/18.
//

#include "RenderTest2D.h"
#include <Tracy.hpp>
#include <TracyOpenGL.hpp>

class PointLight {
public:
    glm::vec3 position;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    float constant;
    float linear;
    float quadratic;
    float enabled;

    void toBuffer(float* flt) {
        ZoneScopedN("PL::ToBuffer");
        int i = 0;

        flt[i++] = position.x;
        flt[i++] = position.y;
        flt[i++] = position.z;
        flt[i++] = 0;


        flt[i++] = ambient.x;
        flt[i++] = ambient.y;
        flt[i++] = ambient.z;
        flt[i++] = 0;

        flt[i++] = diffuse.x;
        flt[i++] = diffuse.y;
        flt[i++] = diffuse.z;
        flt[i++] = 0;

        flt[i++] = specular.x;
        flt[i++] = specular.y;
        flt[i++] = specular.z;
        flt[i++] = 0;

        flt[i++] = constant;
        flt[i++] = linear;
        flt[i++] = quadratic;
        flt[i++] = enabled;
    }

    PointLight(glm::vec3 pos, float constant, float linear, float quadratic, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, bool enabled): position(pos), constant(constant), linear(linear), quadratic(quadratic), ambient(ambient), diffuse(diffuse), specular(specular), enabled(enabled) {}

    PointLight() {}
};

RenderTest2D::RenderTest2D() : Scene() {}

void lightEdit(PointLight* p, int pos) {
    char buff[100];
    snprintf(buff, sizeof(buff), "LightEdit_%i", pos);

    if(ImGui::Begin(buff)) {
        float ambient[3] = {p->ambient.x, p->ambient.y, p->ambient.z};
        float diffuse[3] = {p->diffuse.x, p->diffuse.y, p->diffuse.z};
        float specular[3] = {p->specular.x, p->specular.y, p->specular.z};
        bool enabled = p->enabled == 1.0f;

        ImGui::SliderFloat("X", &p->position.x, -1, 1);
        ImGui::SliderFloat("Y", &p->position.y, -1, 1);

        ImGui::ColorEdit3("Ambient", ambient, ImGuiColorEditFlags_RGB);
        ImGui::ColorEdit3("Diffuse", diffuse, ImGuiColorEditFlags_RGB);
        ImGui::ColorEdit3("Specular", specular, ImGuiColorEditFlags_RGB);
        ImGui::SliderFloat("Linear", &p->linear, 0.1, 1);
        ImGui::SliderFloat("Constant", &p->constant, 0.1, 1);
        ImGui::SliderFloat("Quadratic", &p->quadratic, 0.1, 1);
        ImGui::Checkbox("Enabled", &enabled);

        p->ambient = glm::vec3(ambient[0], ambient[1], ambient[2]);
        p->diffuse = glm::vec3(diffuse[0], diffuse[1], diffuse[2]);
        p->specular = glm::vec3(specular[0], specular[1], specular[2]);

        p->enabled = enabled ? 1.0f : 0.0f;
    }

    ImGui::End();
}


FileShader s("2DVert.glsl", "2DFrag.glsl");
Unknown::VertexInfo verticies;
Unknown::TextureInfo texture;
Unknown::TextureInfo spec;
GLuint lightUBO;

constexpr int ubo_size = 20;//4+ 4+4+4 + 1+1+1;
constexpr int lightBufferSize = ubo_size * 2;
float lightBuffer[lightBufferSize];

PointLight p {};
PointLight p1 (glm::vec3(0.5, 0.5, 0), 0.2, 0.1, 0.4, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), true);

std::vector<PointLight*> lights;

void RenderTest2D::render() const {
    ZoneScopedN("R2D::render");
    TracyGpuZone("Render");
    if(s.prog == -1) {
        ZoneNamedN(level2, "R2D::Setup", true);
        TracyGpuZone("Setup");

        texture = Unknown::getRendererBackend()->loadTexture("crate.png");
        spec = Unknown::getRendererBackend()->loadTexture("crate_spec.png");
        verticies = Unknown::getRendererBackend()->createRectVerticies(0, 0, 1, 1);
        s.compile();

        for (float &i : lightBuffer) {
            i = 0;
        }

        glGenBuffers(1, &lightUBO);
        glBindBuffer(GL_UNIFORM_BUFFER, lightUBO);
        glBufferData(GL_UNIFORM_BUFFER, sizeof(lightBuffer), &lightBuffer[0], GL_DYNAMIC_DRAW);
        //glBindBuffer(GL_UNIFORM_BUFFER, 0);

        lights.push_back(&p);
        lights.push_back(&p1);
    }

    glBindBuffer(GL_UNIFORM_BUFFER, lightUBO);
    void * map = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
    memcpy(map, &lightBuffer[0], sizeof(lightBuffer));
    glUnmapBuffer(GL_UNIFORM_BUFFER);

    float x = 0;
    float y = 0;
    double angle = 0;

    s.bind();

    auto& uk = Unknown::getUnknown();

    float centerX = texture.width / 2.0f;
    float centerY = texture.height / 2.0f;

    // Create the ortagonal projection
    glm::mat4 projection = glm::ortho(0.0f, 1.0f, 1.0f, 0.0f, -100.0f, 0.0f);

    // Create the view matrix
    glm::mat4 view = glm::mat4(1.0f);

    // Create the model matrix
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(x + centerX, y + centerY, 0.5f));
    model = glm::rotate(model, (float) glm::radians(angle), glm::vec3(0, 0, 1.0f));

    model = glm::translate(model, glm::vec3(-centerX, -centerY, 0.0f));

    // Projection * view * model
    glm::mat4 proj = projection * view * model;

    int mx, my;
    SDL_GetMouseState(&mx, &my);
    glm::vec3 tmp = proj * glm::vec4(mx/1024.0, my/1024.0, 0.0f, 1.0f);
    p.position = glm::vec3(tmp.x, tmp.y, 0);

    for(int i = 0; i < lights.size(); i++) {
        lightEdit(lights[i], i);
        lights[i]->toBuffer(&lightBuffer[i * ubo_size]);
    }

    if(ImGui::Begin("Light buffer")) {
        ImGui::Columns(4, "Buffer", true);
        for(int i = 0; i < 4; i++) {
            for (int j = 0; j < lightBufferSize / 4; j++) {
                ImGui::Text("%f", lightBuffer[j * 4 + i]);
            }
            ImGui::NextColumn();
        }
        ImGui::NextColumn();
    }
    ImGui::End();

    glUniformMatrix4fv(glGetUniformLocation(s.prog, "MVP"), 1, GL_FALSE, &proj[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(s.prog, "modelMatrix"), 1, GL_FALSE, &proj[0][0]);
    glUniform1i(glGetUniformLocation(s.prog, "mat.diffuse"), 0);
    glUniform1i(glGetUniformLocation(s.prog, "mat.specular"), 1);
    //TODO: controllable
    s.setFloat("mat.shine", 0.3);

    GLuint lightBlockIndex = glGetUniformBlockIndex(s.prog, "lighting");
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, lightUBO);
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

