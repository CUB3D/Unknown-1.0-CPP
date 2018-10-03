#version 300 es

precision highp float;


struct Material {
    sampler2D diffuse;
    sampler2D specular;

    float shine;
};
uniform Material mat;

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;

in vec3 normal;
in vec3 fragmentPosition;
in vec2 UV;

out vec4 fragColour;

void main() {
    vec3 objectColour = vec3(1, 1, 1);
    vec3 diffuseColour = vec3(texture(mat.diffuse, UV));
    // Use specular texture for spcular hilights
    vec3 specularColour = vec3(texture(mat.specular, UV));

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


    fragColour = vec4((ambientLight + diffuse + specularLight) * objectColour, 1.0f);
}