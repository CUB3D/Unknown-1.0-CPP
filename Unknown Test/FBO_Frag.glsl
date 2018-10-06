#version 300 es
precision highp float;

in vec2 UV;

out vec4 fragColor;

uniform sampler2D fboTexture;

void main() {
    vec4 colour = texture(fboTexture, UV);
    // Colour inverse
    //fragColor = vec4(vec3(1.0f - colour), 1.0f);
    //fragColor = vec4(colour.x, 0, 0, 1.0);
    fragColor = colour;
}
