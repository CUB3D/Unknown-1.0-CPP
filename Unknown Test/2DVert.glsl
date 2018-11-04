#version 300 es

precision highp float;

layout(location = 0) in vec3 inVertex; // Input in model space
layout(location = 1) in vec3 inNormal; // Normal vector
layout(location = 2) in vec2 inUV;

uniform mat4 MVP; // The modelview matrix
uniform mat4 modelMatrix;
//uniform mat4 modelView;

out vec3 normal;
out vec3 fragmentPosition;
out vec2 UV;

void main() {
    UV = inUV;
    normal = mat3(transpose(inverse(modelMatrix))) * inNormal;

    fragmentPosition = vec3(modelMatrix * vec4(inVertex, 1.0));

    gl_Position = MVP * vec4(inVertex, 1.0);
}