#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord; // Texture coordinates attribute

out vec2 TexCoord; // Output texture coordinates to fragment shader

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
    gl_Position = u_Projection * u_View * u_Model * vec4(a_Position, 1.0);
    TexCoord = a_TexCoord; // Pass texture coordinates to fragment shader
}
