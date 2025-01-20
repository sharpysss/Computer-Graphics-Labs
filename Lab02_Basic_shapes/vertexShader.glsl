#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 colour;

out vec3 fragmentColour;

void main()
{
    // Output vertex position
    gl_Position = vec4(position.x, position.y, position.z, 1.0);
    
    // Exercise 1(a)
    // gl_Position = vec4(position.x + 0.5, position.y, position.z, 1.0);
    
    // Exercise 1(b)
    // gl_Position = vec4(position.x, - position.y, position.z, 1.0);
    
    // Exercise 1(c)
    // gl_Position = vec4(position.y, position.x, position.z, 1.0);
    
    // Output vertex colour
    fragmentColour = colour;
}
