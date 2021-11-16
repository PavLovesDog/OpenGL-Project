#include <iostream>
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

//Think of shaders as functions to fun on the GPU

/* GLFloat is just an OpenGL type of float */
// Vertices Coordinates, coordinates for geometry shape
GLfloat vertices[] = 
{
	//COORDINATES				     
	// X ,   Y  ,    Z  
	-1.0f, -1.0f, -0.0f, // top right
	 1.0f,  1.0f, -0.0f, // bottom right
	-1.0f,  1.0f, -0.0f, // bottom left
	 1.0f, -1.0f, -0.0f // top left
};

GLuint indices[] =
{
	0,1,2, // first triangle
	0,3,1 // second triangle
};

int screenWidth{ 800 };
int screenHeight{ 800 };


int main()
{
	// initialise glfw
	glfwInit(); 

	// tell glfw what version of openGl is being used, in this case OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// tell GLFW which profile to use, which is CORE profile, this only uses modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

	// Create window
	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Mandlebrot Viewer", NULL, NULL); // (width, height, title, fullscreened, unknown)
	if (window == NULL) // error check
	{
		std::cout << "Failed to create the GLFW window dude." << std::endl;
		return -1;
	}
	glfwMakeContextCurrent(window); // use the window created, introduced into current context

	// use glad to load configurations of OpenGL
	gladLoadGL();

	glViewport(0, 0, screenWidth, screenHeight); // coordinates of display within window, specifying the viewport

	// call to shader cpp, creates shader object using default.vert & default.frag
	Shader shaderProgram("default.vert", "default.frag");

	// create Vertex Array Object and bind it
	VAO VAO1;
	VAO1.Bind();

	// generate Vertex Buffer Obj & Element Buffer Obj, then links to...
	VBO VBO1(vertices, sizeof(vertices)); // VBO links to vertices
	EBO EBO1(indices, sizeof(indices)); // EBO links to indices

	// link VBO attributes (coordinates & colour) to VAO
	// LinkAttribute(VBO VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
	VAO1.LinkAttribute(VBO1, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0); // stride is 3 * sife of float in bytes
	//VAO1.LinkAttribute(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3*sizeof(float))); // offset between coordin. & RGB's is 3 * float byte size

	// Unbind all objects to prevent accidental modification
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// get ID's of uniform called "scale"
	//GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	// set colour of window background
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // (R, G, B, Opacity)
	glClear(GL_COLOR_BUFFER_BIT); // clean back buffer and assign it a new colour
	glfwSwapBuffers(window); // swap buffers, from front-buffer to back-buffer or vice-versa

	// begin loop to run while window is open
	while (!glfwWindowShouldClose(window))
	{
		// keep window colour
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.Activate(); //activate shader program

		//glUniform1f(uniID, 0.5f); // assign a value to uniform (set size of vertices using uniform variable) NOTE: must be done AFTER SP.activate()

		VAO1.Bind(); // binds VAO for OpenGl to know how to use it

		//glDrawArrays(GL_TRIANGLES, 0, 6); // Draw shape, using GL_TRIANGLES primitive
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // draw shapes with triangle primitives, 9 is vertex amount

		glfwSwapBuffers(window); // swap buffer so image gets updated each frame

		// process all glfw window events
		glfwPollEvents();

	}

	// DELETE all objects created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	glfwDestroyWindow(window); // delete window when program completed
	glfwTerminate(); // terminate GLFW once done
	return 0;
}