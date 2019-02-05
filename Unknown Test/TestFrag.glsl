#version 300 es

precision highp float;


struct Material {
    sampler2D diffuse;
    sampler2D specular;

    float shine;
};
uniform Material mat;

// Directional lights
struct DirectionalLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

// Point lights
struct PointLight {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

// Spotlights
struct SpotLight {
    vec3 position;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float cutOff;
};


in vec3 normal;
in vec3 fragmentPosition;
in vec2 UV;

out vec4 fragColour;

//#define LIGHT_COUNT 1
//
//layout (std140) uniform lighting {
//    DirectionalLight directionalLights[LIGHT_COUNT];
//    PointLight pointLights[LIGHT_COUNT];
//    SpotLight spotlights[LIGHT_COUNT];
//} lightingData;

// Calculate the affect on the colour that is from a particular directional light
vec3 calculateDirectionalLight(DirectionalLight light) {
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
    vec3 reflectDir = reflect(-lightDir, norm);

    float specularStrength = pow(max(dot(viewDir, reflectDir), 0.0), mat.shine);
    vec3 specularLight = specularColour * specularStrength * light.specular;

    return ambientLight + diffuse + specularLight;
}

// Calculate the part of the light that is caused by a given spotlight
vec3 calculateSpotLight(SpotLight light) {

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

//void doLighting() {
//    vec3 diffuseColour = vec3(texture(mat.diffuse, UV));
//    // Use specular texture for spcular hilights
//    vec3 specularColour = vec3(texture(mat.specular, UV));
//
//    vec3 viewPos = vec3(1.0f, 1.0f, 1.0f);
//
//    // Calc ambient light, diffuse often the same as ambient
//    vec3 ambientLight = diffuseColour * light.ambient;
//
//
//    // Calc diffuse light
//    vec3 norm = normalize(normal);
//    vec3 lightDir = normalize(light.position - fragmentPosition);
//
//    float diffuseStrength = max(dot(norm, lightDir), 0.0);
//    vec3 diffuse = (diffuseColour * diffuseStrength) * light.diffuse;
//
//    // Calc specular
//    vec3 viewDir = normalize(viewPos - fragmentPosition);
//    vec3 reflectDir = reflect(-lightDir, norm);
//
//    float specularStrength = pow(max(dot(viewDir, reflectDir), 0.0), mat.shine);
//    vec3 specularLight = specularColour * specularStrength * light.specular;
//
//
//    fragColour = vec4(ambientLight + diffuse + specularLight, 1.0f);
//}

void main() {
    vec3 outCol = vec3(0);

    DirectionalLight d;
    d.ambient = vec3(1, 1, 1);
    d.specular = vec3(1, 1, 1);
    d.diffuse = vec3(1, 1, 1);
    d.direction = vec3(1, 1, 1);

    outCol = calculateDirectionalLight(d);

//    for(int i = 0; i < LIGHT_COUNT; i++) {
//        outCol += calculateDirectionalLight(lightingData.directionalLights[i]);
//        outCol += calculatePointLight(lightingData.pointLights[i]);
//        outCol += calculateSpotLight(lightingData.spotlights[i]);
//    }

    //outCol = vec3(1.0, 0, 0);
    fragColour = vec4(outCol, 1.0);
}