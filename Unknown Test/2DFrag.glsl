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


in vec3 normal;
in vec3 fragmentPosition;
in vec2 UV;

out vec4 fragColour;

#define LIGHT_COUNT 32

layout (std140) uniform lighting {
    PointLight pointLights[LIGHT_COUNT];
//    DirectionalLight directionalLights[LIGHT_COUNT];
    //SpotLight spotlights[LIGHT_COUNT];
} lightingData;

//uniform vec3 lightPos;
//uniform vec3 lightCol;
uniform vec3 viewPos;

float getAttenuation(PointLight light) {
    float distance = length(light.position - fragmentPosition);
    float denom = light.constant + light.linear * distance + light.quadratic * distance * distance;

    if(denom == 0.0f) {
        return -1.0f;
    }

    return 1.0f / denom;
}

vec3 calculatePointLight(PointLight light) {
    if(light.enabled == 0.0f) {
        return vec3(0.0f, 0.0f, 0.0f);
    }

    float attenuation = getAttenuation(light);

    vec3 diffuseTextureColour = vec3(texture(mat.diffuse, UV)) * attenuation;
    vec3 specularTextureColour = vec3(texture(mat.specular, UV)) * attenuation;

    vec3 ambientColour = diffuseTextureColour * light.ambient;

    vec3 n = normalize(normal);
    vec3 lightDir = normalize(light.position - fragmentPosition);
    float diffuseStrength = max(dot(n, lightDir), 0.0);
    vec3 diffuseColour = specularTextureColour * diffuseStrength * light.diffuse;

    vec3 viewDirection = normalize(viewPos - fragmentPosition);
    vec3 reflectDirection = reflect(-lightDir, n);
    float specularStrength = pow(max(dot(viewDirection, reflectDirection), 0.0), mat.shine);
    vec3 specularColour = specularTextureColour * specularStrength * light.specular;

    return ambientColour + diffuseColour + specularColour;
}

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

void main() {

    vec3 colour = vec3(0);

    for(int i = 0; i < LIGHT_COUNT; i++) {
        colour += calculatePointLight(lightingData.pointLights[i]);
//        colour += calculateDirectionalLight(lightingData.directionalLights[i]);
    }

    fragColour = vec4(colour, 1);


//    vec3 viewPos = lightPos;
//
//    vec3 diffuseColour = vec3(texture(mat.diffuse, UV));
//    vec3 specularColour = vec3(texture(mat.specular, UV));
//
//
//    vec3 ambientColour = diffuseColour * 0.1f;
//
//    vec3 n = normalize(normal);
//    vec3 lightDir = normalize(lightPos - fragmentPosition);
//    float diffuseStrength = max(dot(n, lightDir), 0.0);
//    vec3 diffuse = (diffuseColour * diffuseStrength);
//
//    vec3 viewDirection = normalize(viewPos - fragmentPosition);
//    vec3 reflectDirection = reflect(-lightDir, n);
//    float specularStrength = pow(max(dot(viewDirection, reflectDirection), 0.0), 32.0);
//    vec3 specular = specularColour * specularStrength;


    //vec3 diffuse = vec3(0, 0, 0);

//    vec3 outCol = vec3(0);
//
//    for(int i = 0; i < LIGHT_COUNT; i++) {
//        outCol += calculateDirectionalLight(lightingData.directionalLights[i]);
//        outCol += calculatePointLight(lightingData.pointLights[i]);
//        outCol += calculateSpotLight(lightingData.spotlights[i]);
//    }
//
//    //outCol = vec3(1.0, 0, 0);
//    fragColour = vec4(outCol, 1.0);

    //fragColour = vec4((ambientColour + diffuse + specular) * lightCol, 1);
}