//
// Created by cub3d on 19/05/2020.
//

#ifndef UNKNOWN_SPOTLIGHT_H
#define UNKNOWN_SPOTLIGHT_H

#include "glm/glm.hpp"

class SpotLight {
public:
    static constexpr int BUFFER_SIZE = 24;// (3 + 1) + pos
                                        // (3 + 1) + dir
                                        // (3 + 1) + ambient
                                        // (3 + 1) + diffuse
                                        // (3 + 1) + spec
                                        // (1 + 3); // cutoff


    glm::vec3 position {0, 0, 0};
    glm::vec3 direction {0, 0, 0};


    glm::vec3 ambient {0, 0, 0};
    glm::vec3 diffuse {0, 0, 0};
    glm::vec3 specular{0, 0, 0};

    float cutOff {0};

    void toBuffer(float* flt) const;

    SpotLight(glm::vec3 pos, float constant, float linear, float quadratic, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float cutoff): direction(pos), ambient(ambient), diffuse(diffuse), specular(specular), cutOff(cutoff) {}

    SpotLight() = default;

    void show_edit(int pos);
};


#endif //UNKNOWN_SPOTLIGHT_H
