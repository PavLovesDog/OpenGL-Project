#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

/* GLFloat is just an OpenGL type of float */
// Vertices Coordinates, coordinates for geometry shape
GLfloat vertices[] = 
{
	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // lower left corner
	0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // lower right corner
	0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // upper corner
	// below added more vertices for added triangle in middle
	-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
	0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
	0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Inner bottom
};

GLuint indices[] =
{
	0,3,5, // lower left triangle
	3,2,4, // lower right triangle
	5,4,1 // upper triangle
};


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
	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL Window", NULL, NULL); // (width, height, title, fullscreened, unknown)
	if (window == NULL) // error check
	{
		std::cout << "Failed to create the GLFW window dude." << std::endl;
		return -1;
	}
	glfwMakeContextCurrent(window); // use the window created, introduced into current context

	// use glad to load configurations of OpenGL
	gladLoadGL();

	glViewport(0, 0, 800, 800); // coordinates of display within window, specifying the viewport

	// call to shader cpp 
	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkVBO(VBO1, 0);
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

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
		VAO1.Bind(); // binds VAO for OpenGl to know how to use it
		//glDrawArrays(GL_TRIANGLES, 0, 3); // Draw shape, using GL_TRIANGLES primitive
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0); // draw shapes with triangle primitives, 9 is vertex amount
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