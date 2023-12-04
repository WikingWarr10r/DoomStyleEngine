#version 330 core

in vec2 TexCoord; // Input texture coordinates from vertex shader

out vec4 colour;

void main()
{
    colour = vec4(0.2, 0.2, 0.8, 1.0);
}
