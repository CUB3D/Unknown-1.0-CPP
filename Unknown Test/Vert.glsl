#version 300 es

precision highp float;
in vec4 inVertex;
uniform mat4 projmat;

//in vec2 texCoord;
//out vec2 out_texCoord;

void main() {
    //out_texCoord = vec2(0, 0);
    gl_Position = projmat * inVertex;
}