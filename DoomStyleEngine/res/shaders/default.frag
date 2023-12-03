#version 330 core

in vec2 TexCoord; // Input texture coordinates from vertex shader

out vec4 colour;

void main()
{
    colour = vec4(1.0, 1.0, 0.5, 1.0);
}
