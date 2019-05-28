#version 330 core

layout(location = 0) in vec4 position;

uniform mat4 u_Proj;
uniform vec4 u_LineColor;

out vec4 fragmentColor;

void main()
{
    gl_Position = u_Proj * position;
    fragmentColor = u_LineColor;
};
