#version 300 es

precision highp float;

uniform sampler2D texture0;

in vec3 normal;
in vec3 fragmentPosition;
in vec2 UV;

out vec4 fragColour;

void main() {
    vec3 objectColour = vec3(texture(texture0, UV));
    //vec3 objectColour = vec3(0.4f, 0.6f, 0);
    vec3 lightColour = vec3(1.0f, 1.0f, 1.0f);

    vec3 viewPos = vec3(1.0f, 1.0f, 2);
    vec3 lightPos = vec3(1.2f, -1.0f, 2);

    // Calc ambient light
    float ambientStrength = 0.1f;

    vec3 ambientLight = ambientStrength * lightColour;


    // Calc diffuse light
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragmentPosition);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColour;

    // Calc specular
    float specularStrength = 0.9f;
    vec3 viewDir = normalize(viewPos - fragmentPosition);
    vec3 reflectDir = reflect(-lightDir, norm);

    float specularFocus = 128.0f;
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), specularFocus);
    vec3 specularLight = specularStrength * spec * lightColour;


    fragColour = vec4((ambientLight + diffuse + specularLight) * objectColour, 1.0f);
    //fragColour = vec4(objectColour, 1.0f);
}