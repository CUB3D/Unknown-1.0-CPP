//
// Created by cub3d on 18/05/2020.
//

#ifndef UNKNOWN_LIGHTINGMANAGER2D_H
#define UNKNOWN_LIGHTINGMANAGER2D_H

#include "PointLight.h"
#include "DirectionalLight.h"
#include "SpotLight.h"
#include "GL/GL.h"

#include <Tracy.hpp>
#include <Imgui/imgui.h>


#include <vector>
#include <memory>

class LightingManager2D {
public:
    static constexpr int BUFFER_CAPACITY = 2;
    static constexpr int POINT_SIZE = BUFFER_CAPACITY * PointLight::BUFFER_SIZE;
    static constexpr int DIRECTION_SIZE = BUFFER_CAPACITY * DirectionalLight::BUFFER_SIZE;
    static constexpr int SPOT_SIZE = BUFFER_CAPACITY * SpotLight::BUFFER_SIZE;

    static constexpr int LIGHT_BUFFER_SIZE = POINT_SIZE + DIRECTION_SIZE + SPOT_SIZE;
    float* lightBuffer;

    std::vector<std::shared_ptr<PointLight>> pointLights;
    std::vector<std::shared_ptr<DirectionalLight>> directionalLights;
    std::vector<std::shared_ptr<SpotLight>> spotLights;


    GLuint lightUBO {0};

    LightingManager2D();

    void init();

    void updateBuffer();

    void updateLightBuffer();

    void bindBuffer(int index);
};


#endif //UNKNOWN_LIGHTINGMANAGER2D_H
