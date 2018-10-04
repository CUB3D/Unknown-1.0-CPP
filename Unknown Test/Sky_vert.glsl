#version 300 es

precision highp float;

layout(location = 0) in vec3 inUV;

out vec3 UV;

uniform mat4 proj;
uniform mat4 view;

void main() {

    UV = inUV;
    gl_Position = proj * view * vec4(inUV, 1.0);
}
