#version 300 es

precision highp float;

uniform sampler2D texture0;

in vec2 UV;
in vec3 vertexNormal;

out vec4 fragColour;

void main() {
    vec3 lightColour = vec3(1, 1, 0);

    float ambientLightStrength = 1.0;
    vec3 ambient = ambientLightStrength * lightColour;

    // Get the distance from light source
    vec3 light = vec3(0, 0, 0);
    float intencityScale = distance(light, vertexNormal) * 10.0f;

    fragColour = texture(texture0, UV) * vec4(ambient, 1.0) * intencityScale;
}