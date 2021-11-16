#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>

class EBO
{
public:
	// ID reference on Element Buffer Object
	GLuint ID;
	// Constructir that generates a EBO & links it to indices
	EBO(GLuint* indices, GLsizeiptr size);

	// binds EBO
	void Bind();
	// unbinds EBO
	void Unbind();
	// deletes EBO
	void Delete();
};

#endif // !EBO_CLASS_H
