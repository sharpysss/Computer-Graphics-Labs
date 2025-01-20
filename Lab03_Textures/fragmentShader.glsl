#version 330 core

// Input
in vec2 UV;

// Output
out vec3 colour;

// Uniforms
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;

void main()
{
    // colour = vec3(texture(texture3, UV));
    colour = vec3(mix(texture(texture1, UV), texture(texture2, UV), 0.7));
    
    // Only show Mario texture
    // colour = vec3(texture(texture2, uv));
    
    // Exercise 2 - Make Mario face to the right
    // colour = vec3(texture(texture2, vec2(-uv.x, uv.y)));
}
