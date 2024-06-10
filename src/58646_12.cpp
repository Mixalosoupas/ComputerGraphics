#include <GL/glew.h>
#include <iostream>
#include <Shader.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

//¢ÓÊÇÓÇ 2 - 58646 ÊÁÑÁ×ÁÔÆÇÓ ÌÉ×ÁÇË


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

glm::mat4 trans = glm::mat4(1.0f);

glm::vec3 movRight = glm:: vec3(0.1f, 0.0f, 0.0f);
glm::vec3 movLeft = glm::vec3(-0.1f, 0.0f, 0.0f);
glm::vec3 movUp = glm::vec3(0.0f, 0.1f, 0.0f);
glm::vec3 movDown = glm::vec3(0.0f, -0.1f, 0.0f);

float speed = 0.5f;


float boundaryRight = 1.0f;
float boundaryLeft = -1.0f;
float boundaryTop = 1.0f;
float boundaryBottom = -1.0f;

void ProcessInput(GLFWwindow* givenWindow , glm::mat4& transform)
{
	glm::vec3 translation(0.0f);

	if (glfwGetKey(givenWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(givenWindow, true);

	if (glfwGetKey(givenWindow, GLFW_KEY_W) == GLFW_PRESS)
		translation += movUp*speed;
	if (glfwGetKey(givenWindow, GLFW_KEY_S) == GLFW_PRESS)
		translation += movDown*speed;
	if (glfwGetKey(givenWindow, GLFW_KEY_A) == GLFW_PRESS)
		translation += movLeft*speed;
	if (glfwGetKey(givenWindow, GLFW_KEY_D) == GLFW_PRESS)
		translation += movRight*speed;

	glm::vec4 currentPosition = transform * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	glm::vec4 newPosition = currentPosition + glm::vec4(translation, 0.0f);

	if (newPosition.x < boundaryRight && newPosition.x > boundaryLeft &&
		newPosition.y < boundaryTop && newPosition.y > boundaryBottom) {
		transform = glm::translate(transform, translation);
	}
}





void genPolygon(float* vertices, int numOfVertices) {

	const float PI = 3.14159265358979323846f;
	float scale = 0.5f;


	for (int i = 0; i < numOfVertices; i++) {
		float angle = i * 2.0f * PI / numOfVertices;
		vertices[3 * i] = scale * cos(angle);      // x-coordinate
		vertices[3 * i + 1] = scale * sin(angle);	// y-coordinate
		vertices[3 * i + 2] = 0.0f;					    // z-coordinate
	}

}


int main() {

	std::cout << "Project 2.3" << std::endl;

	// Initialize GLFW
	if (!glfwInit()) {
		std::cout << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	// Create window
	GLFWwindow* window = glfwCreateWindow(800, 600, "Project 2.2", NULL, NULL);

	// Check if the window is created.
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Make the context that is created the current one
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Set our viewport --> we tell openGL how to render everything that we give.
	glViewport(0, 0, 800, 600);

	// Create callback function
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//Create Nonagon
	const int numPoints = 7;
	const int numVertices = (3 * numPoints);
	GLfloat vertices[numVertices];
	genPolygon(vertices, numPoints);



	//VBO1
	GLuint vertexBufferId2;
	glGenBuffers(1, &vertexBufferId2);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void*)0);
	glEnableVertexAttribArray(0);


	Shader shaderProgram1("res/Shaders_58646/VertexShader_12.txt", "res/Shaders_58646/FragmentShader_12.txt");

	ImVec4 non_color = ImVec4(0.1f, 0.5f, 0.6f, 1.00f); // Color of Nonagon


	while (!glfwWindowShouldClose(window)) {

		ProcessInput(window,trans);


		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Use Shader Program
		glUseProgram(shaderProgram1.ID);
	 
		// Send the transformation matrix to the shader
		int transformLoc = glGetUniformLocation(shaderProgram1.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

		// Get the current position of the polygon
		glm::vec3 currentPosition = glm::vec3(trans[3][0], trans[3][1], trans[3][2]);


		// Set the color uniform
		int uniformLocation = glGetUniformLocation(shaderProgram1.ID, "color1");
		glUniform3f(uniformLocation, currentPosition.x + 0.5, currentPosition.y + 0.5, 0);

		// Draw Nonagon
		glDrawArrays(GL_POLYGON, 0, numPoints);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}