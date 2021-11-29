/*
    Like the fragment shader, the vertex shader is also run once per pixel through the GPU simulataneously,
    this will set the position of each vertex to be worked on.
    The aPos variable relates to the VBO with the vertices bound to location 0. 
    These positions are then passed through OpenGl which track the vertex location on the GPU.
    This is essentially telling the GPU where the buffer attached to the vertex is.
*/

#version 330 core
layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}