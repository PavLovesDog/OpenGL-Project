#include"shaderClass.h"

std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	//Create Objects / Shaders
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);// create a reference to store our vertex shader
	glShaderSource(vertexShader, 1, &vertexSource, NULL); // attach the Vertex Shader source to VS object
	glCompileShader(vertexShader); // compile VS into machine code

	// Create Fragment Shader & get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL); //Attach the FS source code to FS object
	glCompileShader(fragmentShader); // Compile FS into machine code

	//wrap up compiled shaders into shader program
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);   // attach VS & FS to the shader program
	glAttachShader(ID, fragmentShader); //      "   "			"   "
	glLinkProgram(ID); // wrap-up/link all shaders together in shader program

	// Delete the now useless Vertex & Fragment Shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}