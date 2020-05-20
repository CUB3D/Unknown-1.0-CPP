//
// Created by cub3d on 18/05/2020.
//

#ifndef UNKNOWN_DIRECTONALLIGHT_H
#define UNKNOWN_DIRECTONALLIGHT_H

#include "glm/glm.hpp"

class DirectionalLight {
public:
    static constexpr int BUFFER_SIZE = 20;// (3 + 1) + dir
                                       // (3 + 1) + ambient
                                       // (3 + 1) + diffuse
                                       // (3 + 1) + spec
                                       // (1 + 3); // enable


    glm::vec3 direction {0, 0, 0};

    glm::vec3 ambient {0, 0, 0};
    glm::vec3 diffuse {0, 0, 0};
    glm::vec3 specular{0, 0, 0};

    float enabled {0};

    void toBuffer(float* flt) const;

    DirectionalLight(glm::vec3 pos, float constant, float linear, float quadratic, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, bool enabled): direction(pos), ambient(ambient), diffuse(diffuse), specular(specular), enabled(enabled) {}

    DirectionalLight() = default;

    void show_edit(int pos);
};

#endif //UNKNOWN_POINTLIGHT_H
