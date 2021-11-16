#include"VAO.h"

// Constructor that generates a VAO ID
VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

// Links a VBO attributes (i.e positions, colour, type etc.) to the VAO using a certain layout
void VAO::LinkAttribute(VBO VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	VBO.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset); // CONFIGURE the Vertex Atribute so OpenGl knows how to read VAO
	glEnableVertexAttribArray(layout); //ENABLE the Vertex Attribute so OpneGL knows how to use it
	VBO.Unbind();
}

// binds the VAO
void VAO::Bind()
{
	glBindVertexArray(ID);
}

// Unbinds VAO
void VAO::Unbind()
{
	glBindVertexArray(0);
}

// Deletes VAO
void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}