#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Shader.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"

Camera myCamera(glm::vec3(0.0f, 0.0f, 3.0f));

float deltaTime = 0.0f;
float currentFrameTime = 0.0f;
float previousFrameTime = 0.0f;

float previousMousePositonX = 400.0f;
float previousMousePositonY = 300.0f;

bool firstMouse = true;

void FrameBufferSizeCallback(GLFWwindow* givenWindow, int givenWidth, int givenHeight)
{
	glViewport(0, 0, givenWidth, givenHeight);
}

void ProcessInput(GLFWwindow* givenWindow)
{
	if (glfwGetKey(givenWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(givenWindow, true);
}




int main()
{

	// Initialization

	if (!glfwInit())
	{
		std::cout << "Failed to initialize glfw!" << std::endl;
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Lab3", NULL, NULL);

	if (!window)
	{
		std::cout << "Failed to initialize the window!" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	// Set the callback function
	glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);


	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize glew!" << std::endl;
		glfwTerminate();
		return -1;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;

	//Data


	GLfloat vertices[] = {
		//position            //color             
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0,
		0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0,
		0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0,
		-0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0,
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0,

		-0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0,
		0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0,
		0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0,
		0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0,
		-0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0,

		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,

		0.5f,  0.5f,  0.5f,  0.0f, 0.5f, 0.0f,
		0.5f,  0.5f, -0.5f,  0.0f, 0.5f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 0.5f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 0.5f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.5f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f, 0.5f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.5f,
		0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.5f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.5f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.5f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.5f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.5f,

		-0.5f,  0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.5f, 0.0f, 0.0f
	};

	glm::vec3 cubePositions[] =
	{
	  glm::vec3(0.0f,  0.0f,  -12.0f),
	  glm::vec3(2.0f,  2.0f, -12.0f),
	  glm::vec3(3.0f, 2.5f, -12.0f),
	};


	// first buffer (vbo)
	unsigned int vertexBufferId;
	glGenBuffers(1, &vertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	Shader shaderProgram("res/Shaders_58646/VertexShader_31.txt", "res/Shaders_58646/FragmentShader_31.txt");

	glm::mat4 identity = glm::mat4(1.0f);

	glEnable(GL_DEPTH_TEST);

	glDepthFunc(GL_LESS);


	const char* glsl_version = "#version 330";
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);




	//Scale Factors
	glm::vec3 scale1 = { 1.6f, 1.6f, 1.6f };
	glm::vec3 scale2 = { 1.4f, 1.4f, 1.4f };
	glm::vec3 scale3 = { 1.6f, 1.6f, 1.6f };

	float speed1 = 30.0f;
	float speed2 = 20.0f;
	float speed3 = 80.0f;
	float speed4 = 80.0f;
	float speed5 = 80.0f;

	float angle1 = 0.0f;
	float angle2 = 0.0f;
	float angle3 = 0.0f;
	float angle4 = 0.0f;
	float angle5 = 0.0f;

	float radius12;
	float radius23;

	float factor1 = 0;
	float factor2 = 0;

	bool rot1 = true;
	bool rot2 = true;
	bool rot3 = true;
	bool rot4 = true;
	bool rot5 = true;

	float a1 = 0;
	float a2 = 0;
	float a3 = 0;
	float a4 = 0;
	float a5 = 0;


	// Game loop

	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window);

		glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		
		
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::SetNextWindowSize(ImVec2(800 / 4, 150));

		ImGui::Begin("Speed orbit!");

		ImGui::SliderFloat("Speed1", &speed1,5.0f,100.0f);
		ImGui::SliderFloat("Speed2", &speed2,5.0f,100.0f);
		ImGui::SliderFloat("Speed3", &speed3,40.0f,400.0f);
		ImGui::SliderFloat("Speed4", &speed4,20.0f,400.0f);
		ImGui::SliderFloat("Speed5", &speed5,20.0f,400.0f);

		ImGui::Begin("Rotation!");
		ImGui::Checkbox("Rotation1", &rot1);
		ImGui::Checkbox("Rotation2", &rot2);
		ImGui::Checkbox("Rotation3", &rot3);
		ImGui::Checkbox("Rotation4", &rot4);
		ImGui::Checkbox("Rotation5", &rot5);

		ImGui::SetNextWindowPos(ImVec2(0,300));
		ImGui::SetNextWindowSize(ImVec2(800 / 3, 75));

		ImGui::Begin("Radius offset!");

		ImGui::SliderFloat("Radius12", &factor1, 0.0f, 2.5f);
		ImGui::SliderFloat("Radius23", &factor2, 0.0f, 3.0f);		

		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());



		float time = glfwGetTime();

		currentFrameTime = time;
		deltaTime = currentFrameTime - previousFrameTime;
		previousFrameTime = currentFrameTime;

		angle1 += glm::radians(deltaTime) * speed1;
		angle2 += glm::radians(deltaTime) * speed2;
		angle3 += glm::radians(deltaTime) * speed3;
		angle4 += glm::radians(deltaTime) * speed4;
		angle5 += glm::radians(deltaTime) * speed5;





		// Render Using the shader program
		shaderProgram.use();


		glm::mat4 view;
		view = myCamera.GetViewMatrix(); // now we get the view matrix form the camrera class -------------
		int viewLocation = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

		glm::mat4 projection;


		// 3D
		projection = glm::perspective(glm::radians(myCamera.Zoom), 800.0f / 600.0f, 0.3f, 100.0f); // now we get the zoom form the camera class ---------------------
		int projectionLocation = glGetUniformLocation(shaderProgram.ID, "projection");
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

		//Create First cube
		glm::mat4 model;
		

		model = glm::translate(identity, cubePositions[0]);
		

		// Rotation 1
		//Get the position of the 1st cube
		glm::vec3 modelRt = glm::vec3(model[3][0], model[3][1], model[3][2]);
		
		float currentTime;
		float currentAngle;

		if (rot1) {
			model = glm::rotate(model, angle1, glm::vec3(0.0f, 1.0f, 0.0f));
			a1 = angle1;
			
		}
		else 
		{
			model = glm::rotate(model, a1, glm::vec3(0.0f, 1.0f, 0.0f));
			angle1 = a1;

		}
		model = glm::scale(model, scale1);

		int modelLocation1 = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(modelLocation1, 1, GL_FALSE, &model[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		

		//Create Second Cube
		glm::mat4 model2 = glm::mat4(1.0f);

		
		radius12 = glm::length(cubePositions[1] - cubePositions[0] + factor1);


		//Rotation 2
		if (rot2) 
		{
			model2 = glm::translate(identity, cubePositions[0]);
			model2 = glm::rotate(model2, angle2, glm::vec3(0.0f, 1.0f, 0.0f));
			model2 = glm::translate(model2, glm::vec3(radius12, cubePositions[1].y, 0.0f));
			a2 = angle2;
		}
		else {
			model2 = glm::translate(identity, cubePositions[0]);
			model2 = glm::rotate(model2, a2, glm::vec3(0.0f, 1.0f, 0.0f));
			model2 = glm::translate(model2, glm::vec3(radius12, cubePositions[1].y, 0.0f));
			angle2 = a2;
		}
	
		
		// Rotation 4
		if (rot4) 
		{
			model2 = glm::rotate(model2, angle4, glm::vec3(0.0f, 1.0f, 0.0f));
			a4 = angle4;
		}
		else 
		{
			model2 = glm::rotate(model2, a4, glm::vec3(0.0f, 1.0f, 0.0f));
			angle4 = a4;
		}

		model2 = glm::scale(model2, scale2);

		int modelLocation2 = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(modelLocation2, 1, GL_FALSE, &model2[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glm::vec3 model2Rt = glm::vec3(model2[3][0], model2[3][1], model2[3][2]);
		

		//Create Third Cube
		glm::mat4 model3 = glm::mat4(1.0f);

		float radius3 = glm::length(cubePositions[2] - cubePositions[0]);

		//Rotation 2
		if (rot2) 
		{
			model3 = glm::translate(identity, cubePositions[0]);
			model3 = glm::rotate(model3, angle2, glm::vec3(0.0f, 1.0f, 0.0f));
			model3 = glm::translate(model3, glm::vec3(radius3, cubePositions[2].y, 0.0f));
			a2 = angle2;
		}
		else 
		{
			model3 = glm::translate(identity, cubePositions[0]);
			model3 = glm::rotate(model3, a2, glm::vec3(0.0f, 1.0f, 0.0f));
			model3 = glm::translate(model3, glm::vec3(radius3, cubePositions[2].y, 0.0f));
			angle2 = a2;
			
		}

		glm::vec3 model3Rt = glm::vec3(model3[3][0], model3[3][1], model3[3][2]);
		
		
		radius23 = glm::length(model3Rt - model2Rt + factor2);

		//Rotation 3 
		if (rot3) 
		{
			model3 = glm::translate(identity, model2Rt);
			model3 = glm::rotate(model3, angle3, glm::vec3(0.0f, 1.0f, 0.0f));
			model3 = glm::translate(model3, glm::vec3(radius23, cubePositions[2].y, 0.0f));
			a3 = angle3;
		}
		else
		{
			model3 = glm::translate(identity, model2Rt);
			model3 = glm::rotate(model3, a3, glm::vec3(0.0f, 1.0f, 0.0f));
			model3 = glm::translate(model3, glm::vec3(radius23, cubePositions[2].y, 0.0f));
			angle3 = a3;
		}
		

		// Rotation 5
		if (rot5)
		{
			model3 = glm::rotate(model3, angle5, glm::vec3(0.0f, 1.0f, 0.0f));
			a5 = angle5;
		}
		else
		{
			model3 = glm::rotate(model3, a5, glm::vec3(0.0f, 1.0f, 0.0f));
			angle5 = a5;
		}

		model3 = glm::scale(model3, scale3);

		int modelLocation3 = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(modelLocation3, 1, GL_FALSE, &model3[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}