// Open GL
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Open GL specific math lib
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

// Standard libs
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

// Abstraction classes for Open GL
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Renderer.h"

// Game Logic classes
#include "Terrain.h"
#include "HelpPoint.h"
#include "Texture.h"
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>


// Global variables
GLFWwindow* window;
int monitorWidth, monitorHeight, windowWidth, windowHeight;
Terrain terrain;

int initWindow() {
	/* Initialize the library */
	if (!glfwInit())
		return -1;
	windowWidth = 1600;
	windowHeight = 900;

	glfwGetMonitorWorkarea(glfwGetPrimaryMonitor(), nullptr, nullptr, &monitorWidth, &monitorHeight);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(windowWidth, windowHeight, "Procedural Terrain Flight", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	
	glfwSetWindowPos(window, (monitorWidth - windowWidth)/2, (monitorHeight - windowHeight)/2);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);


	return 0;
}

void update() {

	terrain.update();
	 
}

void render(Renderer renderer, Shader shader) {
	
	
	// Clear the screen
	renderer.clear();
	terrain.render(renderer, shader);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}

}

int main(void)
{
	

	if (initWindow() == -1) {
		return -1;
	}

	if (glewInit() != GLEW_OK) {
		std::cout << "Error with glew" << std::endl;
		return -1;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;

	glfwSetKeyCallback(window, key_callback );
	
	
	// Shaders
	Shader shader("res/shaders/Basic.shader");
	shader.bind();
	
	// Texture
	
	// Model matrix
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(-65.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.1, 0.1, 0.1));
	
	
	// View matrix
	glm::mat4 view = glm::mat4(1.0f); 
	view = glm::translate(view, glm::vec3(-5.0f, -2.0f, -1.0f));
	

	// Projection matrix
	glm::mat4 projection;
	projection = glm::perspective(glm::radians(80.0f), (float)windowWidth / (float)windowHeight, 0.1f, 1000.0f);

	
	// Change projection matrix in shader
	

	shader.setUniformMat4f("model", model);
	shader.setUniformMat4f("view", view);
	shader.setUniformMat4f("projection", projection);

	//shader.setUniformMat4f("transform", trans);


	
	Renderer renderer;

	double targetFrameRate = 20.0f;
	double currentTime;
	double lastTime = 0.0f;
	double waitTime = 1.0f / targetFrameRate;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		currentTime = glfwGetTime();

		if (currentTime - lastTime >= waitTime) {
			
			lastTime = currentTime;
			/* Update here */
			update();
		}
			

			/* Render here */
			render(renderer, shader);

			/* Swap front and back buffers */
			glfwSwapBuffers(window);


			/* Poll for and process events */
			glfwPollEvents();
			
	}
	
	glfwTerminate();
	return 0;
}


