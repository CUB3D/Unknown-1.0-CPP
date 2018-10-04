//
// Created by cub3d on 03/10/18.
//

#include "RenderingPipeline3D.h"
#include "FileShader.h"
#include "../GL/GL.h"
#include "../Utils.h"

void RenderingPipeline3D::render() {
    s.bind(true);

    // TODO: change to uniform blocks for lights

    for(int i = 0; i < directionalLights.size(); i++) {
        std::string arr = "directionalLights[" + Unknown::intToString(i) + "]";

        s.setVec3((arr + ".ambient").c_str(), 0.1f, 0.1f, 0.1f);
        s.setVec3((arr + ".diffuse").c_str(), 0.3f, 0.3f, 0.3f);
        s.setVec3((arr + ".specular").c_str(), 1.0f, 1.0f, 1.0f);
        s.setVec3((arr + ".direction").c_str(), -0.2f, -1.0f, -0.3f);
    }
    // point

    for(int i = 0; i < pointLights.size(); i++) {
        std::string arr = "pointLights[" + Unknown::intToString(i) + "]";

        s.setVec3((arr + ".ambient").c_str(), 0.2f, 0.2f, 0.2f);
        s.setVec3((arr + ".diffuse").c_str(), 0.5f, 0.5f, 0.5f);
        s.setVec3((arr + ".specular").c_str(), 1.0f, 1.0f, 1.0f);
        s.setVec3((arr + ".position").c_str(), 1.0f, 2.0f, -9.0f);

        s.setFloat((arr + ".constant").c_str(), 1.0f);
        s.setFloat((arr + ".linear").c_str(), 0.09f);
        s.setFloat((arr + ".quadratic").c_str(), 0.032f);
    }

//    // spot
//
//    s.setVec3("spotlights[0].ambient", 0.2f, 0.2f, 0.2f);
//    s.setVec3("spotlights[0].diffuse", 0.5f, 0.5f, 0.5f);
//    s.setVec3("spotlights[0].specular", 1.0f, 1.0f, 1.0f);
//    s.setVec3("spotlights[0].position", 1.0f, 2.0f, 1.0f);
//
//    s.setVec3("spotlights[0].direction", 0, -1, 0);
//    s.setFloat("spotlights[0].cutOff", glm::cos(glm::radians(12.5f)));

    for(auto& mesh : meshes) {
        mesh->render(s, *this);
    }

    s.unbind();
}

RenderingPipeline3D::RenderingPipeline3D() : s(FileShader("Test.glsl", "TestFrag.glsl")) {
    this->projectionMatrix = Unknown::glmhPerspectivef2(45.0f, 1.0f, 0.1f, 100.0f);
}

Camera3D &RenderingPipeline3D::getCamera() {
    return this->camera;
}
