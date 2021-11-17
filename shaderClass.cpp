#include"shaderClass.h"

// Reads a text file and outputs a string with everything in it
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

// Constructor that builds the shader program from 2 shaders
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	// Read veertex file & fragment file and store strings
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	// convert the shader source strings into char arrays
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	//Create Objects / Shaders
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);// create a reference to store our vertex shader
	glShaderSource(vertexShader, 1, &vertexSource, NULL); // attach the Vertex Shader source to VS object
	glCompileShader(vertexShader); // compile VS into machine code
	compileErrors(vertexShader, "VERTEX"); // check for compilation errors

	// Create Fragment Shader & get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL); //Attach the FS source code to FS object
	glCompileShader(fragmentShader); // Compile FS into machine code
	compileErrors(fragmentShader, "FRAGMENT"); // check for linking errors

	//wrap up compiled shaders into shader program
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);   // attach VS & FS to the shader program
	glAttachShader(ID, fragmentShader); //      "   "			"   "
	glLinkProgram(ID); // wrap-up/link all shaders together in shader program
	compileErrors(ID, "PROGRAM");

	// Delete the now useless Vertex & Fragment Shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

// Activates the shader program
void Shader::Activate()
{
	glUseProgram(ID);
}

// Deletes the shader program
void Shader::Delete()
{
	glDeleteProgram(ID);
}

void Shader::set_vec4(const std::string& name, glm::vec4 vec) const
{
	glUniform4f(glGetUniformLocation(ID, name.c_str()), vec.x, vec.y, vec.z, vec.w);
}

// checks if the different shaders have compiled properly
void Shader::compileErrors(unsigned int shader, const char* type)
{
	GLint hasCompiled;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for: " << type << "\n" << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for: " << type << "\n" << std::endl;
		}
	}
}