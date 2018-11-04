//
// Created by cub3d on 31/10/18.
//

#include "RenderTest2D.h"

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
};

RenderTest2D::RenderTest2D() : Scene("R2D") {

}

FileShader s("2DVert.glsl", "2DFrag.glsl");
Unknown::VertexInfo verticies;
Unknown::TextureInfo texture;
Unknown::TextureInfo spec;
GLuint lightUBO;

constexpr int ubo_size = 20;//4+ 4+4+4 + 1+1+1;
float lightBuffer[ubo_size * 2];

void RenderTest2D::render() const {

    if(s.prog == -1) {
        texture = Unknown::getRendererBackend()->loadTexture("/home/cub3d/Downloads/crate.png");
        spec = Unknown::getRendererBackend()->loadTexture("/home/cub3d/Downloads/crate_spec.png");
        verticies = Unknown::getRendererBackend()->createRectVerticies(0, 0, 1, 1);
        s.compile();

        for(int i = 0; i < 40; i++) {
            lightBuffer[i] = 0;
        }

        glGenBuffers(1, &lightUBO);
        glBindBuffer(GL_UNIFORM_BUFFER, lightUBO);
        glBufferData(GL_UNIFORM_BUFFER, sizeof(lightBuffer), &lightBuffer[0], GL_DYNAMIC_DRAW);
        //glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

    glBindBuffer(GL_UNIFORM_BUFFER, lightUBO);
    void * map = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
    memcpy(map, &lightBuffer[0], sizeof(lightBuffer));
    glUnmapBuffer(GL_UNIFORM_BUFFER);



    ImGui::Begin("Render");


    static float ambient[3];
    static float diffuse[3];
    static float specular[3];
    static float linear, consta, quad;
    static float shine;
    static bool enabled;

    ImGui::ColorEdit3("Ambient", ambient, ImGuiColorEditFlags_RGB);
    ImGui::ColorEdit3("Diffuse", diffuse, ImGuiColorEditFlags_RGB);
    ImGui::ColorEdit3("Specular", specular, ImGuiColorEditFlags_RGB);
    ImGui::SliderFloat("Linear", &linear, 0, 1);
    ImGui::SliderFloat("Constant", &consta, 0, 1);
    ImGui::SliderFloat("Quadratic", &quad, 0, 1);
    ImGui::SliderFloat("Shine", &shine, 1, 256);
    ImGui::Checkbox("Enabled", &enabled);

    ImGui::End();

    float x = 0;
    float y = 0;
    double angle = 0;

    s.bind();

    auto& uk = Unknown::getUnknown();

    float centerX = texture.width / 2.0f;
    float centerY = texture.height / 2.0f;

    // Create the ortagonal projection
    glm::mat4 projection = glm::ortho(0.0f, 1.0f, 1.0f, 0.0f, -100.0f, 0.0f);
    //projection = Unknown::glmhPerspectivef2(45.0, 16.0/9.0, -100.0f, -0.1f);

    //s.setVec3("lightPos", 0.5, 0.5, 1);

    // Create the view matrix
    glm::mat4 view = glm::mat4(1.0f);

    // Create the model matrix
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(x + centerX, y + centerY, 0.5f));
    model = glm::rotate(model, (float) glm::radians(angle), glm::vec3(0, 0, 1.0f));

  // model = glm::rotate(model, (float) glm::radians(1.0f), glm::vec3(1.0f, 0, 0));


    model = glm::translate(model, glm::vec3(-centerX, -centerY, 0.0f));

    // Projection * view * model
    glm::mat4 proj = projection * view * model;

    int mx, my;
    SDL_GetMouseState(&mx, &my);
    glm::vec3 tmp = proj * glm::vec4(mx/1024.0, my/1024.0, 0.0f, 1.0f);
   // s.setVec3("lightPos", tmp.x, tmp.y, 0);
   // s.setVec3("viewPos", tmp.x, tmp.y, 0);
  //  s.setVec3("lightCol", lr, lg, lb);

    PointLight p;
    p.position = glm::vec3(tmp.x, tmp.y, 0);

    p.ambient = glm::vec3(ambient[0], ambient[1], ambient[2]);
    p.diffuse = glm::vec3(diffuse[0], diffuse[1], diffuse[2]);
    p.specular = glm::vec3(specular[0], specular[1], specular[2]);

    p.linear = linear;
    p.constant = consta;
    p.quadratic = quad;
    p.enabled = enabled ? 1.0f : 0.0f;

    p.toBuffer(&lightBuffer[0]);

    PointLight p1;
    p1.position = glm::vec3(0.5, 0.5, 0);
    p1.linear = 0.2;
    p1.constant = 0.1;
    p1.quadratic = 0.4;
    p1.ambient = glm::vec3(1.0f, 1.0f, 1.0f);
    p1.diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
    p1.specular = glm::vec3(1.0f, 1.0f, 1.0f);
    p1.enabled = 1.0f;
    p1.toBuffer(&lightBuffer[20]);


    glUniformMatrix4fv(glGetUniformLocation(s.prog, "MVP"), 1, GL_FALSE, &proj[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(s.prog, "modelMatrix"), 1, GL_FALSE, &proj[0][0]);
    glUniform1i(glGetUniformLocation(s.prog, "mat.diffuse"), 0);
    glUniform1i(glGetUniformLocation(s.prog, "mat.specular"), 1);
    s.setFloat("mat.shine", shine);

    GLuint lightBlockIndex = glGetUniformBlockIndex(s.prog, "lighting");
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, lightUBO);
    glUniformBlockBinding(s.prog, lightBlockIndex, 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, (GLuint)texture.pointer);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, (GLuint) spec.pointer);

    glBindVertexArray(verticies.vao);

    // Render data
    //TODO: should store vertex count in vertexinfo
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // Unbind stuff
   // glBindVertexArray(0);
   // s.unbind();
}
