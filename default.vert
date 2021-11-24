/*
    Like the fragment shader, the vertex shader is also run once per pixel through the GPU simulataneously,

*/

#version 330 core
layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}