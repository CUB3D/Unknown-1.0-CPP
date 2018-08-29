#version 300 es

precision highp float;

uniform vec4 inputColour;
out vec4 fragColour;

void main() {
    fragColour = inputColour;
}