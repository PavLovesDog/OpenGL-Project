#include <iostream>
#include <vector>
#include <algorithm> // for std::sort
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <stb\stb_image.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

// Vertices Coordinates, coordinates for geometry shape
GLfloat vertices[] = 
{
	//COORDINATES				     
	// X ,   Y  ,    Z  
    -1.0f, -1.0f, -0.0f,  
	 1.0f,  1.0f, -0.0f,  
	-1.0f,  1.0f, -0.0f,   
	 1.0f, -1.0f, -0.0f
	 
};

// Indices for vertex coordinates
GLuint indices[] =
{
	0, 1, 2, // first triangle
	0, 3, 1, // second triangle
};


// Global Variables
float screenWidth{ 1280 },
	  screenHeight{ 960 };
// variables for maving around image
float centerX{ 0.0f };
float centerY{ 0.0f };
float zoom{ 1.0f };
float zoomOutSpeed{ 1.25f }; // lower number for slower zoom out
float zoomInSpeed{ 0.85f }; // high number for slower zoom in (1 being the highest)
float speed{ 0.025f };


// Initialise the GLFW, determine which profile to use
void initialise()
{
	// initialise glfw
	glfwInit();

	// tell glfw what version of openGl is being used, in this case OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// tell GLFW which profile to use, which is CORE profile, this only uses modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

}

// handle Resize-ing of window
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// Error checks window creation, sets the initial background colour,
// Sets up viewport / GL window configurations & brings window into current context for use
void setup_GLwindow(GLFWwindow* window)
{
	if (window == NULL) // error check
	{
		std::cout << "Failed to create the GLFW window dude." << std::endl;
		//return -1;
	}
	glfwMakeContextCurrent(window); // use the window created, introduced into current context

	// use glad to load configurations of OpenGL
	gladLoadGL();

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// set colour of window background
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // (R, G, B, Opacity)
	glClear(GL_COLOR_BUFFER_BIT); // clean back buffer and assign it a new colour
	glfwSwapBuffers(window); // swap buffers, from front-buffer to back-buffer or vice-versa
}

// links the VBO attributes to the VAO & unbinds after use to prevent errors
void unbind_link_shaders(VAO VAO1, VBO VBO1, EBO EBO1)
{
	// link VBO attributes (coordinates & colour) to VAO
	VAO1.LinkAttribute(VBO1, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0); // stride is 3 * sife of float in bytes

	// Unbind all objects to prevent accidental modification
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
}

// Handles the panning, zooming & quit functions
// code sourced: see README.txt
void handle_input(GLFWwindow* window)
{
	// if user hits 'Esc', close the window
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	// if user hits 'arrow up', move up
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		centerY = centerY + speed * zoom;
		if (centerY > 1.0f) centerY = 1.0f; // cap centerY for set speed
	}

	// if user hits 'arrow down', move down
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		centerY = centerY - speed * zoom;
		if (centerY < -1.0f) centerY = -1.0f; 
	}

	// if user hits 'arrow left', move left
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		centerX = centerX - speed * zoom;
		if (centerX < -1.0f) centerX = -1.0f;
	}

	// if user hits 'arrow right', move right
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		centerX = centerX + speed * zoom;
		if (centerX > 1.0f) centerX = 1.0f;
	}

	// user presses 'minus' key on numpad, zoom out
	if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS)
	{
		zoom = zoom * zoomOutSpeed;
		if (zoom > 1.0f) zoom = 1.0f;
	}

	// user presses 'plus' key on numpad, zoom in
	if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS)
	{
		zoom = zoom * zoomInSpeed;
		if (zoom < 0.0005f) zoom = 0.0005f;
	}
}

// Function to sort the read pixel data and find the first
// non zero numbers to determine colour for each fragment.
// code sourced: see README.txt
glm::vec4 find_ranges(std::vector<float> &data)
{
	std::sort(data.begin(), data.end()); // arrange elements in ascending order
	int size = data.size();
	int lowest = 0;
	while (data[lowest] == 0.0f) // search for the first non-zero number
	{
		++lowest;
		if (lowest == size - 1) break; // ensure vector iterator does NOT access elements out of range
	}

	int length = size - lowest; // find total values within range
	glm::vec4 ranges = glm::vec4(data[lowest], data[lowest + length * 3 / 4 - 1], data[lowest + length * 7 / 8 - 1], data[size - 1]);
	/*		  ranges =  first non-zero number, roughly 3/4's of remaining ranges, 7/8's of remaining sorted iterations, */
	return ranges;
}

int main()
{
	// Initialise GLFW
	initialise();

	// Create window (width, height, title, fullscreened, unknown);
	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Charlies Mandlebrot Viewer", NULL, NULL);
	setup_GLwindow(window);

	// call to shader cpp, creates shader object using default.vert & default.frag
	Shader shaderProgram("default.vert", "default.frag");
	
	// create Vertex Array Object and bind it
	VAO VAO1;
	VAO1.Bind();
	// generate Vertex Buffer Obj & Element Buffer Obj, then links to...
	VBO VBO1(vertices, sizeof(vertices)); // VBO links to vertices
	EBO EBO1(indices, sizeof(indices)); // EBO links to indices
	unbind_link_shaders(VAO1, VBO1, EBO1); // unbind and link shaders!

	glEnable(GL_DEPTH_TEST); // enable for our color_ranges to determine depth of fragments, to determine colour


	std::vector<float> pixel_data(screenWidth * screenHeight, 0.0f); // vector to store current pixel data in
	glm::vec4 color_ranges = glm::vec4(0.0f, 0.5f, 0.66667f, 1.0f); // initial vec for colour ranges

	// begin loop to run while window is open
	while (!glfwWindowShouldClose(window))
	{
		// keep window colour
		glClearColor(0.2f, 0.0f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram.Activate(); //activate shader program

		// send/retireve uniform variable values to fragment shader
		glUniform1f(glGetUniformLocation(shaderProgram.ID, "zoom"), zoom);
		glUniform1f(glGetUniformLocation(shaderProgram.ID, "centerX"), centerX);
		glUniform1f(glGetUniformLocation(shaderProgram.ID, "centerY"), centerY);
		glUniform4f(glGetUniformLocation(shaderProgram.ID, "color_ranges"), color_ranges.x, 
																			color_ranges.y, 
																			color_ranges.z, 
																			color_ranges.w);

		VAO1.Bind(); // binds VAO for OpenGl to know how to use it

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // draw shapes with triangle primitives, 6 is vertex amount

		// read the colour ranges of pixels on screen, save to pixel data
		glReadPixels(0, 0, screenWidth, screenHeight, GL_DEPTH_COMPONENT, GL_FLOAT, pixel_data.data()); 
		color_ranges = find_ranges(pixel_data); // set new colour to pass into 'color_ranges' next pass

		glfwSwapBuffers(window); // swap buffer so image gets updated each frame
		
		// process all glfw window & input events
		glfwPollEvents();
		handle_input(window);
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