#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include"VBO.h"

class VAO
{
public:
	// ID reference for Vertext Array Object (VAO)
	GLuint ID;
	// Constructor that generates a VAO ID
	VAO();

	// Links a VBO attributes (i.e positions, colour, type etc.) to the VAO using a certain layout
	void LinkAttribute(VBO VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	// binds the VAO
	void Bind();
	// Unbinds the VAO
	void Unbind();
	// Deletes VAO
	void Delete();

};

#endif