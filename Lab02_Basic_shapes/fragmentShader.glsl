#version 330 core

//Input
in vec2 UV;
//output

out vec3 colour;

//Uniforms
uniform sampler2D textureMap;
void main()
{
    colour = vec3(texture(textureMap, UV));
}
