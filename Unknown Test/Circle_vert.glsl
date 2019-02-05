#version 300 es
precision highp float;

layout (location = 0) in vec3 vertex;

uniform mat4 projmat;

void main() {
    gl_Position = projmat * vec4(vertex, 1.0f);
}
