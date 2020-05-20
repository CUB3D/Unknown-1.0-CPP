//
// Created by cub3d on 18/05/2020.
//

#ifndef UNKNOWN_POINTLIGHT_H
#define UNKNOWN_POINTLIGHT_H

#include "glm/glm.hpp"

class PointLight {
public:
    static constexpr int BUFFER_SIZE = 20;// (3 + 1) + pos
                                       // (3 + 1) + ambient
                                       // (3 + 1) + diffuse
                                       // (3 + 1) + spec
                                       // 1 + 1 + 1 + 1; // bools


    glm::vec3 position {0, 0, 0};

    glm::vec3 ambient {0, 0, 0};
    glm::vec3 diffuse {0, 0, 0};
    glm::vec3 specular{0, 0, 0};

    float constant {0.01};
    float linear {0.01};
    float quadratic {0.01};
    float enabled {0};

    void toBuffer(float* flt) const;

    PointLight(glm::vec3 pos, float constant, float linear, float quadratic, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, bool enabled): position(pos), constant(constant), linear(linear), quadratic(quadratic), ambient(ambient), diffuse(diffuse), specular(specular), enabled(enabled) {}

    PointLight() = default;

    void show_edit(int pos);
};

#endif //UNKNOWN_POINTLIGHT_H
