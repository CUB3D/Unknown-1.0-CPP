#version 300 es

precision highp float;

layout(location = 0) in vec3 inVertex; // Input in model space
layout(location = 1) in vec4 inColour;
layout(location = 2) in vec2 vertexUV; // Input tex coord for this vertex
layout(location = 3) in vec3 inVertexNormal; // The normal for this vertex

out vec2 UV;
out vec3 vertexNormal;

uniform mat4 MVP; // The modelview matrix

void main() {
    UV = vertexUV;
    vertexNormal = inVertexNormal;

    gl_Position = MVP * vec4(inVertex, 1.0);
}