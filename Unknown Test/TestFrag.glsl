#version 300 es

precision highp float;


struct Material {
    sampler2D diffuse;
    sampler2D specular;

    float shine;
};
uniform Material mat;

// Point lights
struct PointLight {
    vec3 position;
    float padding0;

    vec3 ambient;
    float padding1;
    vec3 diffuse;
    float padding2;
    vec3 specular;
    float paddding3;

    float constant;
    float linear;
    float quadratic;
    float enabled;
};

// Directional lights
struct DirectionalLight {
    vec3 direction;
    float padding0;

    vec3 ambient;
    float padding1;

    vec3 diffuse;
    float padding2;

    vec3 specular;
    float padding3;

    float enabled;
    float padding4;
    float padding5;
    float padding6;
};


// Spotlights
struct SpotLight {
    vec3 position;
    float padding0;

    vec3 direction;
    float padding1;

    vec3 ambient;
    float padding2;
    vec3 diffuse;
    float padding3;
    vec3 specular;
    float padding4;

    float cutOff;
    float enabled;
    float padding6;
    float padding7;
};


in vec3 normal;
in vec3 fragmentPosition;
in vec2 UV;

out vec4 fragColour;

#define LIGHT_COUNT 2

layout (std140) uniform lighting {
    PointLight pointLights[LIGHT_COUNT];
    DirectionalLight directionalLights[LIGHT_COUNT];
    SpotLight spotlights[LIGHT_COUNT];
} lightingData;

// Calculate the affect on the colour that is from a particular directional light
vec3 calculateDirectionalLight(DirectionalLight light) {
    if(light.enabled == 0.0f) {
        return vec3(0.0f, 0.0f, 0.0f);
    }

    vec3 diffuseColour = vec3(texture(mat.diffuse, UV));
    // Use specular texture for spcular hilights
    vec3 specularColour = vec3(texture(mat.specular, UV));

    vec3 viewPos = vec3(1.0f, 1.0f, 1.0f);

    // Calc ambient light, diffuse often the same as ambient
    vec3 ambientLight = diffuseColour * light.ambient;


    // Calc diffuse light
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(-light.direction);

    float diffuseStrength = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = (diffuseColour * diffuseStrength) * light.diffuse;

    // Calc specular
    vec3 viewDir = normalize(viewPos - fragmentPosition);
    vec3 reflectDir = reflect(-lightDir, norm);

    float specularStrength = pow(max(dot(viewDir, reflectDir), 0.0), mat.shine);
    vec3 specularLight = specularColour * specularStrength * light.specular;

    return ambientLight + diffuse + specularLight;
}

// Calculate the affect on the colour that is from a particular point light
vec3 calculatePointLight(PointLight light) {
    if(light.enabled == 0.0f) {
        return vec3(0.0f, 0.0f, 0.0f);
    }

    float distance = length(light.position - fragmentPosition);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

    vec3 diffuseColour = vec3(texture(mat.diffuse, UV)) * attenuation;
    // Use specular texture for spcular hilights
    vec3 specularColour = vec3(texture(mat.specular, UV)) * attenuation;

    vec3 viewPos = vec3(1.0f, 1.0f, 1.0f);

    // Calc ambient light, diffuse often the same as ambient
    vec3 ambientLight = diffuseColour * light.ambient;


    // Calc diffuse light
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - fragmentPosition);

    float diffuseStrength = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = (diffuseColour * diffuseStrength) * light.diffuse;

    // Calc specular
    vec3 viewDir = normalize(viewPos - fragmentPosition);

//     Phong
//    vec3 reflectDir = reflect(-lightDir, norm);
//    float specularStrength = pow(max(dot(viewDir, reflectDir), 0.0), mat.shine);

    //Blinn-phong
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float specularStrength = pow(max(dot(normal, halfwayDir), 0.0), 16.0);

    vec3 specularLight = specularColour * specularStrength * light.specular;

    return ambientLight + diffuse + specularLight;
}

// Calculate the part of the light that is caused by a given spotlight
vec3 calculateSpotLight(SpotLight light) {
    if(light.enabled == 0.0f) {
        return vec3(0.0f, 0.0f, 0.0f);
    }

    vec3 diffuseColour = vec3(texture(mat.diffuse, UV));
    // Use specular texture for spcular hilights
    vec3 specularColour = vec3(texture(mat.specular, UV));

    vec3 viewPos = vec3(1.0f, 1.0f, 1.0f);

    // Calc ambient light, diffuse often the same as ambient
    vec3 ambientLight = diffuseColour * light.ambient;


    // Calc diffuse light
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - fragmentPosition);

    if(dot(lightDir, normalize(-light.direction)) > light.cutOff) {
        float diffuseStrength = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = (diffuseColour * diffuseStrength) * light.diffuse;

        // Calc specular
        vec3 viewDir = normalize(viewPos - fragmentPosition);
        vec3 reflectDir = reflect(-lightDir, norm);

        float specularStrength = pow(max(dot(viewDir, reflectDir), 0.0), mat.shine);
        vec3 specularLight = specularColour * specularStrength * light.specular;

        return ambientLight + diffuse + specularLight;
    } else {
        return ambientLight;
    }
}

void main() {
    vec3 outCol = vec3(0);

    for(int i = 0; i < LIGHT_COUNT; i++) {
        outCol += calculateDirectionalLight(lightingData.directionalLights[i]);
        outCol += calculatePointLight(lightingData.pointLights[i]);
        outCol += calculateSpotLight(lightingData.spotlights[i]);
    }

    fragColour = vec4(outCol, 1.0);
}