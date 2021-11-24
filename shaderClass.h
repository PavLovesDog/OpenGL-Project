#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<glm\glm.hpp>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

std::string get_file_contents(const char* filename);

class Shader
{
public:
	// Reference ID of the shader program
	GLuint ID;
	// Constructor that builds the shader program from 2 shaders
	// i.e vertShader (default.vert) & fragShader (default.frag)
	Shader(const char* vertexFile, const char* fragmentFile);

	// activates the shader program
	void Activate();
	// deletes the shader program
	void Delete();

private:
	// checks if the different shaders have compiled properly
	void compileErrors(unsigned int shader, const char* type);
};


#endif // !SHADER_CLASS_H