#version 300 es
precision highp float;

out vec4 fragColor;

uniform vec4 inputColour;
uniform int radius;
uniform vec2 centre;

void main() {
    // Discard all outside of radius from centre
    float xDiff = (gl_FragCoord.x - centre.x);
    float yDiff = (gl_FragCoord.y - centre.y);
    float hpot = abs(xDiff * xDiff + yDiff*yDiff);
    float r2 = float(radius*radius);

    if(hpot < r2) {
        fragColor = inputColour;
    } else {
        discard;
    }
}
