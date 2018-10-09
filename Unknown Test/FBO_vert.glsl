#version 300 es
precision highp float;

layout (location = 0) in vec2 vertex;
layout (location = 1) in vec2 inUV;

out vec2 UV;

void main() {
    UV = inUV;
    gl_Position = vec4(vertex.x, vertex.y, 0.0, 1.0);
}
