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


//¢” «”« 1 - 58646  ¡—¡◊¡‘∆«” Ã…◊¡«À
// u = 58646 mod 6 = 2--> ID 2 & 4
// ≈–‘¢√ŸÕœ  ¡… ≈ÕÕ≈¢√ŸÕœ

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}


bool flag = false;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		if (flag == true) {
			flag = false;
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		else {
			flag = true;
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}

	}

}



void ProcessInput(GLFWwindow* givenWindow)
{
	if (glfwGetKey(givenWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(givenWindow, true);

}





void genPolygon(float* vertices, int numOfVertices) {

	const float PI = 3.14159265358979323846f;
	float scale = 0.5f;

	
	for (int i = 0; i < numOfVertices + 1; i++) {
		float angle = i * 2.0f * PI / numOfVertices;
		vertices[3 * i] = scale * cos(angle);      // x-coordinate
		vertices[3 * i + 1] = scale * sin(angle);	// y-coordinate
		vertices[3 * i + 2] = 0.0f;					    // z-coordinate
	}

}


int main() {

	std::cout << "Project 2.1 - 58646 " << std::endl;

	// Initialize GLFW
	if (!glfwInit()) {
		std::cout << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	// Create window
	GLFWwindow* window = glfwCreateWindow(800, 600, "Project 2.1 - 58646", NULL, NULL);

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

	// Create Heptagon
		const int numofPoints1 = 7;
	const int numVertices1 = (3 * numofPoints1);
	GLfloat vertices1[numVertices1];
	genPolygon(vertices1, numofPoints1);

	GLuint VAO1, VBO1;
	glGenVertexArrays(1, &VAO1);
	glGenBuffers(1, &VBO1);
	glBindVertexArray(VAO1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	// Create Nonagon
	const int numofPoints2 = 9;
	const int numVertices2 = (3 * numofPoints2);
	GLfloat vertices2[numVertices2];
	genPolygon(vertices2, numofPoints2);

	GLuint VAO2, VBO2;
	glGenVertexArrays(1, &VAO2);
	glGenBuffers(1, &VBO2);
	glBindVertexArray(VAO2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);



	

	const char* glsl_version = "#version 330";
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// Setup Dear ImGui style
	ImGui::StyleColorsClassic();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);


	Shader shaderProgram1("res/Shaders_58646/VertexShader_11.txt", "res/Shaders_58646/FragmentShader_11.txt");
	Shader shaderProgram2("res/Shaders_58646/VertexShader_21.txt", "res/Shaders_58646/FragmentShader_21.txt");
	
	ImVec4 hep_color = ImVec4(0.5f, 0.2f, 0.6f, 1.00f); // Color of Heptagon
	ImVec4 non_color = ImVec4(0.1f, 0.5f, 0.6f, 1.00f); // Color of Nonagon

	glfwSetKeyCallback(window, key_callback);

	while (!glfwWindowShouldClose(window)) {

		ProcessInput(window);
		
		
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::SetNextWindowSize(ImVec2(800 / 2, 150));
		
		ImGui::Begin("Color Heptagon!");

		ImGui::SliderFloat("R1", &hep_color.x, 0, 1);
		ImGui::SliderFloat("G1", &hep_color.y, 0, 1);
		ImGui::SliderFloat("B1", &hep_color.z, 0, 1);
		
		ImGui::SetNextWindowPos(ImVec2(800 / 2, 0));
		ImGui::SetNextWindowSize(ImVec2(800 / 2, 150));
		
		ImGui::Begin("Color Nonagon!");

		ImGui::SliderFloat("R2", &non_color.x, 0, 1);
		ImGui::SliderFloat("G2", &non_color.y, 0, 1);
		ImGui::SliderFloat("B2", &non_color.z, 0, 1);
		
		
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		
		// Draw Heptagon
		shaderProgram1.use();
		glUniform3f(glGetUniformLocation(shaderProgram1.ID, "color1"), hep_color.x, hep_color.y, hep_color.z);
		glBindVertexArray(VAO1);
		glDrawArrays(GL_POLYGON, 0, numofPoints1);
		glBindVertexArray(0);

		// Draw Nonagon
		shaderProgram2.use();
		glUniform3f(glGetUniformLocation(shaderProgram2.ID, "color1"), non_color.x, non_color.y, non_color.z);
		glBindVertexArray(VAO2);
		glDrawArrays(GL_POLYGON, 0, numofPoints2);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

  glfwTerminate();
  return 0;
}