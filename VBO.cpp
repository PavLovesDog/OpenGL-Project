#include"VBO.h"

// Constructir that generates a VBO & links it to vertices
VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID); // bind the VBO, specifying its a GL_ARRAY_BUFFER
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW); // introduce vertices into the VBO
}

// Binds VBO
void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

// Unbinds VBO
void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Deletes VBO
void VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}
