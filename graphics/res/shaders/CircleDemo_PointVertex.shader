#version 330 core

layout(location = 0) in vec4 position;

uniform float u_PointSize;
uniform vec4 u_PointColor;

out vec4 fragmentColor;

void main()
{
    gl_Position = position;
    gl_PointSize = u_PointSize;
    fragmentColor = u_PointColor;
};
