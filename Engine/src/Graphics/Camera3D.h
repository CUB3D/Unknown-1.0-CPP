//
// Created by cub3d on 04/10/18.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_CAMERA3D_H
#define UNKNOWN_DEVELOPMENT_TOOL_CAMERA3D_H

#include <glm/ext.hpp>
#include <glm/glm.hpp>

class Camera3D {
    glm::vec3 cameraPos   = glm::vec3(0);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

    float yaw;
    float pitch;


    glm::mat4 viewMatrix;

public:
    float cameraSpeed;

    bool lockMouse {false};

    Camera3D();

    void updateViewMatrix();

    void onMouseMove();

    void forwards();
    void backwards();
    void left();
    void right();

    glm::mat4& getViewMatrix();
};


#endif //UNKNOWN_DEVELOPMENT_TOOL_CAMERA3D_H
