#version 330 core

layout(location = 0) in vec3 aPos;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTexCoord;

out vec4 ourColor;
out vec2 texCoord;

uniform vec4 newColor;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    //gl_Position = vec4(aPos, 1.0); // default position
    gl_Position = projection * view * model * vec4(aPos, 1.0); // MVP view
    ourColor = vec4(aColor, 1.0) + newColor; // apply modified color
    texCoord = aTexCoord; // apply texture
}