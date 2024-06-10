#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Shader2.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Camera_58646.h"

// 58646 U = 1 --> ID 1,2,3,5,7

Camera myCamera(glm::vec3(0.0f, 0.0f, 8.0f));

float deltaTime = 0.0f;
float currentFrameTime = 0.0f;
float previousFrameTime = 0.0f;

float previousMousePositonX = 400.0f;
float previousMousePositonY = 300.0f;

bool firstMouse = true;
bool cameraMovementEnabled = true;

void FrameBufferSizeCallback(GLFWwindow* givenWindow, int givenWidth, int givenHeight)
{
	glViewport(0, 0, givenWidth, givenHeight);
}

void ProcessInput(GLFWwindow* givenWindow)
{
	
	
	if (glfwGetKey(givenWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(givenWindow, true);

	if (glfwGetKey(givenWindow, GLFW_KEY_W) == GLFW_PRESS)
		myCamera.ProcessKeyboard(FORWARD, deltaTime);

	if (glfwGetKey(givenWindow, GLFW_KEY_S) == GLFW_PRESS)
		myCamera.ProcessKeyboard(BACKWARD, deltaTime);

	if (glfwGetKey(givenWindow, GLFW_KEY_A) == GLFW_PRESS)
		myCamera.ProcessKeyboard(LEFT, deltaTime);

	if (glfwGetKey(givenWindow, GLFW_KEY_D) == GLFW_PRESS)
		myCamera.ProcessKeyboard(RIGHT, deltaTime);

	if (glfwGetKey(givenWindow, GLFW_KEY_E) == GLFW_PRESS)
		myCamera.ProcessKeyboard(UP, deltaTime);

	if (glfwGetKey(givenWindow, GLFW_KEY_Q) == GLFW_PRESS)
		myCamera.ProcessKeyboard(DOWN, deltaTime);

	if (glfwGetKey(givenWindow, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		myCamera.MovementSpeed = 8.0f;
	else
		myCamera.MovementSpeed = 2.5f;
}

void MousPositionCallback(GLFWwindow* givenWindow, double givenMousePositionX, double givenMousePositionY)
{
	//std::cout << givenMousePositionX << std::endl;
	//std::cout << givenMousePositionY << std::endl;

	if (firstMouse)
	{
		previousMousePositonX = givenMousePositionX;
		previousMousePositonY = givenMousePositionY;

		firstMouse = false;
	}

	float offsetX = givenMousePositionX - previousMousePositonX;
	float offsetY = previousMousePositonY - givenMousePositionY;
	previousMousePositonX = givenMousePositionX;
	previousMousePositonY = givenMousePositionY;


	if (cameraMovementEnabled) 
	{
		myCamera.ProcessMouseMovement(offsetX, offsetY);
	}
	else 
	{
		myCamera.ProcessMouseMovement(0, 0);
	}
	
}



void ScrollCallback(GLFWwindow* givenWindow, double givenScrollOffsetX, double givenScrollOffsetY)
{
	myCamera.ProcessMouseScroll(givenScrollOffsetY);
}

bool flag = true;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_PRESS) {
		if (cameraMovementEnabled)
		{
			cameraMovementEnabled = false;
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			
		}
		else 
		{
			cameraMovementEnabled = true;
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			
			
		}

	}

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
	glfwSetScrollCallback(window, ScrollCallback);
	glfwSetCursorPosCallback(window, MousPositionCallback);
	//glfwSetMouseButtonCallback(window, Mouse_button_callback);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize glew!" << std::endl;
		glfwTerminate();
		return -1;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;

	//Data


	//--Vertex Data
	float vertices[] =
	{
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,


		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f

	};

	glm::vec3 cubePositions[] =
	{
	  glm::vec3(0.0f,  0.0f,  0.0f),
	  glm::vec3(2.0f,  5.0f, -15.0f),
	  glm::vec3(-1.5f, -2.2f, -2.5f),
	  glm::vec3(-3.8f, -2.0f, -12.3f),
	  glm::vec3(2.4f, -0.4f, -3.5f),
	  glm::vec3(-1.7f,  3.0f, -7.5f),
	  glm::vec3(1.3f, -2.0f, -2.5f),
	  glm::vec3(1.5f,  2.0f, -2.5f),
	  glm::vec3(1.5f,  0.2f, -1.5f),
	  glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	// Generate the VAO and VBO
	unsigned int VBO, cubeVAO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(cubeVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	unsigned int lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);


	Shader shaderProgram("res/Shaders_58646/VertexShader_14.txt", "res/Shaders_58646/FragmentShader_14.txt");
	Shader lightSourceShaderProgram("res/Shaders_58646/LightSourceVertexShader_14.txt", "res/Shaders_58646/LightSourceFragmentShader_14.txt");


	glm::mat4 identity = glm::mat4(1.0f);

	glm::vec3 matAmbient[] =
	{
		glm::vec3(0.0215f,  0.1745f,  0.0215f),
		glm::vec3(0.135f,0.2225f,0.1575f),
		glm::vec3(0.05375f,0.05f,0.06625f),
		glm::vec3(0.25f,0.20725f,0.20725f),
		glm::vec3(0.1745f,0.01175f,0.01175f),
		glm::vec3(0.1f, 0.18725f, 0.1745f),
		glm::vec3(0.329412f,0.223529f,0.027451f),
		glm::vec3(0.2125f,0.1275f,0.054f),
		glm::vec3(0.25f,0.25f,0.25f),
		glm::vec3(0.19125f,0.0735f,0.0225f)
	};

	glm::vec3 matDiffuse[] =
	{
		glm::vec3(0.07568f,	0.61424f,0.07568f),
		glm::vec3(0.54f,0.89f,0.63f),
		glm::vec3(0.18275f,0.17f,0.22525f),
		glm::vec3(1.0f,0.829f,0.829f),
		glm::vec3(0.61424f,0.04136f,0.04136f),
		glm::vec3(0.396f,0.74151f,0.69102f),
		glm::vec3(0.780392f,0.568627f,0.113725f),
		glm::vec3(0.714f,0.4284f,0.18144f),
		glm::vec3(0.4f,0.4f,0.4f),
		glm::vec3(0.7038f,0.27048f,0.0828f)
	};

	; glm::vec3 matSpecular[] =
	{
		glm::vec3(0.633f,0.727811f,	0.633f),
		glm::vec3(0.316228f,0.316228f,0.316228f),
		glm::vec3(0.332741f,0.328634f,0.346435f),
		glm::vec3(0.296648f,0.296648f,0.296648f),
		glm::vec3(0.727811f,0.626959f,0.626959f),
		glm::vec3(0.297254f,0.30829f,0.306678f),
		glm::vec3(0.992157f,0.941176f,0.807843f),
		glm::vec3(0.393548f,0.271906f,0.166721f),
		glm::vec3(0.774597f,0.774597f,0.774597f),
		glm::vec3(0.256777f,0.137622f,0.086014f)
	};

	float matShininess[] = { 0.6f, 0.1f , 0.3f , 0.088f, 0.6f , 0.1f , 0.21794872f , 0.2f , 0.6f , 0.1f };


	glm::vec3 lightSourceColor(1.0f, 1.0f, 1.0f);


	glm::vec3 lightSourcePositions[]
	{
		glm::vec3(-3.0f, 1.0f, -10.0f),
		glm::vec3(0.0f, 0.0f, -3.0f),
		glm::vec3(3.4f, 4.0f, -14.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, -10.0f, -10.0f),
		glm::vec3(10.0f, 10.0f, -10.0f),

	};

	glm::vec3 lightSourceDirections[]
	{
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(-1.0f, -1.0f, 0.0f)

	};
	int numPointLights = 4;
	int numDirLights = 2;
	shaderProgram.use();
	float distance[] = { 20 , 32 , 50 , 65 ,100 };

	float angle = 0;
	float radius = 2.0f;


	float lin[] = { 0.22,0.14 , 0.09 , 0.070 , 0.045 };
	float quad[] = { 0.2 , 0.07 , 0.032 , 0.017 , 0.0075 };

	static int e = 0;


	bool pLights = true;
	bool dLights = true;
	bool pId[] = { true,true,true,true };
	bool dId[] = { true,true };


	const char* glsl_version = "#version 330";
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// Setup Dear ImGui style
	//ImGui::StyleColorsDark();
	ImGui::StyleColorsClassic();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);



	glEnable(GL_DEPTH_TEST);

	glDepthFunc(GL_LESS);



	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetKeyCallback(window, key_callback);

	bool shift;
	float vel;

	// Game loop

	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window);

		float time = glfwGetTime();

		currentFrameTime = time;
		deltaTime = currentFrameTime - previousFrameTime;
		previousFrameTime = currentFrameTime;

		angle += glm::radians(deltaTime) * 40.0f;

		glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



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
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);// now we get the zoom form the camera class ---------------------

		shaderProgram.setMat4("projection", projection);
		float linear;
		float quadr;





		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::SetNextWindowSize(ImVec2(800 / 3, 75));
		ImGui::Begin("Radius of the Light!");

		ImGui::SliderFloat("Radius", &radius, 2.0f, 10.0f);

		ImGui::SetNextWindowPos(ImVec2(0, 80));
		ImGui::SetNextWindowSize(ImVec2(800 / 3, 150));
		ImGui::Begin("Radio Buttons!");
		ImGui::RadioButton("RadioButon1", &e, 0);
		ImGui::SameLine();
		ImGui::RadioButton("RadioButon2", &e, 1);
		
		ImGui::RadioButton("RadioButon3", &e, 2);
		ImGui::SameLine();
		ImGui::RadioButton("RadioButon4", &e, 3);
		
		ImGui::RadioButton("RadioButon5", &e, 4);

		ImGui::SetNextWindowPos(ImVec2(0, 240));
		ImGui::SetNextWindowSize(ImVec2(800 / 3, 300));
     	ImGui::Begin("Lights");
		ImGui::Checkbox("PointLights", &pLights);
		ImGui::Checkbox("DirLights", &dLights);
		ImGui::Checkbox("Point Light ID[0]", &pId[0]);
		ImGui::Checkbox("Point Light ID[1]", &pId[1]);
		ImGui::Checkbox("Point Light ID[2]", &pId[2]);
		ImGui::Checkbox("Point Light moving", &pId[3]);
		ImGui::Checkbox("Directional Light ID[0]", &dId[0]);
		ImGui::Checkbox("Directinoal Light ID[1]", &dId[1]);

		ImGui::Render();



		for (int i = 0; i < 5; i++)
		{
			if (e == i )
			{
				linear = lin[i];
				quadr = quad[i];
			}

		}



		





		//PointLights

		//PointLight Source ( That orbits ) 
		glm::mat4 model1 = glm::translate(identity, lightSourcePositions[3]);
		model1 = glm::rotate(model1, angle, glm::vec3(0.0f, 0.0f, 1.0f));
		model1 = glm::translate(model1, glm::vec3(radius, radius, 0.0f));
		glm::vec3 modelV3 = glm::vec3(model1[3][0], model1[3][1], model1[3][2]);

		lightSourcePositions[3] = modelV3;
	
		if (pLights)
		{
			

			shaderProgram.setInt("numPointLights", numPointLights);

			for (int i = 0; i < numPointLights; i++)
			{
				std::string index = std::to_string(i);

				if (pId[i]) 
				{
					shaderProgram.setVec3("pointLight[" + index + "].position", lightSourcePositions[i]);
					shaderProgram.setVec3("pointLight[" + index + "].ambient", glm::vec3(0.5f));
					shaderProgram.setVec3("pointLight[" + index + "].diffuse", glm::vec3(1.0f));
					shaderProgram.setVec3("pointLight[" + index + "].specular", glm::vec3(1.0f));
					shaderProgram.setFloat("pointLight[" + index + "].constant", 1.0f);
					shaderProgram.setFloat("pointLight[" + index + "].linear", linear);
					shaderProgram.setFloat("pointLight[" + index + "].quadratic", quadr);
				}
				else 
				{
					shaderProgram.setVec3("pointLight[" + index + "].position", lightSourcePositions[i]);
					shaderProgram.setVec3("pointLight[" + index + "].ambient", glm::vec3(0.0f));
					shaderProgram.setVec3("pointLight[" + index + "].diffuse", glm::vec3(0.0f));
					shaderProgram.setVec3("pointLight[" + index + "].specular", glm::vec3(0.0f));
					shaderProgram.setFloat("pointLight[" + index + "].constant", 1.0f);
					shaderProgram.setFloat("pointLight[" + index + "].linear", linear);
					shaderProgram.setFloat("pointLight[" + index + "].quadratic", quadr);
				}

			}
		}
		else 
		{
			for (int i = 0; i < numPointLights; i++)
			{
				std::string index = std::to_string(i);

					shaderProgram.setVec3("pointLight[" + index + "].position", lightSourcePositions[i]);
					shaderProgram.setVec3("pointLight[" + index + "].ambient", glm::vec3(0.0f));
					shaderProgram.setVec3("pointLight[" + index + "].diffuse", glm::vec3(0.0f));
					shaderProgram.setVec3("pointLight[" + index + "].specular", glm::vec3(0.0f));
					shaderProgram.setFloat("pointLight[" + index + "].constant", 0.0f);
					shaderProgram.setFloat("pointLight[" + index + "].linear", linear);
					shaderProgram.setFloat("pointLight[" + index + "].quadratic", quadr);
				

			}
		}

		//Directional Lights
		
		
		if (dLights)
		{		
			shaderProgram.setInt("numDirLights", numDirLights);
			for (int i = 0; i < numDirLights; i++)
			{
				std::string index = std::to_string(i);
				if (dId[i])
				{
					shaderProgram.setVec3("dirLight[" + index + "].direction", lightSourceDirections[i]);
					shaderProgram.setVec3("dirLight[" + index + "].ambient", glm::vec3(0.05f));
					shaderProgram.setVec3("dirLight[" + index + "].diffuse", glm::vec3(0.4f));
					shaderProgram.setVec3("dirLight[" + index + "].specular", glm::vec3(0.5f));
				}
				else 
				{
					shaderProgram.setVec3("dirLight[" + index + "].direction", lightSourceDirections[i]);
					shaderProgram.setVec3("dirLight[" + index + "].ambient", glm::vec3(0.00f));
					shaderProgram.setVec3("dirLight[" + index + "].diffuse", glm::vec3(0.0f));
					shaderProgram.setVec3("dirLight[" + index + "].specular", glm::vec3(0.0f));
				}
			}
		}
		else 
		{
			shaderProgram.setInt("numDirLights", numDirLights);
			for (int i = 0; i < numDirLights; i++)
			{
				std::string index = std::to_string(i);
		
				shaderProgram.setVec3("dirLight[" + index + "].direction", lightSourceDirections[i]);
				shaderProgram.setVec3("dirLight[" + index + "].ambient", glm::vec3(0.00f));
				shaderProgram.setVec3("dirLight[" + index + "].diffuse", glm::vec3(0.0f));
				shaderProgram.setVec3("dirLight[" + index + "].specular", glm::vec3(0.0f));
			}
		}


		//Draw cubes
		glBindVertexArray(cubeVAO);
		for (int i = 0; i < 10; i++)
		{

			// Material
			shaderProgram.setVec3("material.ambientColor", matAmbient[i]);
			shaderProgram.setVec3("material.diffuseColor", matDiffuse[i]);
			shaderProgram.setVec3("material.specularColor", matSpecular[i]);
			shaderProgram.setFloat("material.shininess", 128.0f * matShininess[i]);

			glm::mat4 model;

			model = glm::translate(identity, cubePositions[i]);
			model = glm::rotate(model, glm::radians(20.0f) * i, glm::vec3(1.0f, 0.3f, 0.5f));

			shaderProgram.setMat4("model", model);

			glm::mat3 normalTransformation = glm::transpose(glm::inverse(glm::mat3(model)));
			shaderProgram.setMat3("normalTransformation", normalTransformation);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}


		// Draw the light sources
		glBindVertexArray(lightVAO);
		lightSourceShaderProgram.use();
		lightSourceShaderProgram.setMat4("view", view);
		lightSourceShaderProgram.setMat4("projection", projection);
		


		for (unsigned int i = 0; i < 4; i++)
		{
			if (pId[i] && pLights) 
			
			{
				lightSourceShaderProgram.setVec3("lightSourceColor", glm::vec3(1.0f, 1.0f, 1.0f));
				glm::mat4 modelMatrix = glm::mat4(1.0f);
				modelMatrix = glm::translate(modelMatrix, lightSourcePositions[i]);
				//modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
				lightSourceShaderProgram.setMat4("model", modelMatrix);

				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
			else 
			{
				lightSourceShaderProgram.setVec3("lightSourceColor", glm::vec3(0.0f, 0.0f, 0.0f));

				glm::mat4 modelMatrix = glm::mat4(1.0f);
				modelMatrix = glm::translate(modelMatrix, lightSourcePositions[i]);
				//modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
				lightSourceShaderProgram.setMat4("model", modelMatrix);

				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
		}


		


		for (unsigned int i = 4; i < 6; i++)
		{
			if (dId[i-4] && dLights)
			{
				lightSourceShaderProgram.setVec3("lightSourceColor", glm::vec3(1.0f, 1.0f, 1.0f));
				glm::mat4 modelMatrix = glm::mat4(1.0f);
				modelMatrix = glm::translate(modelMatrix, lightSourcePositions[i]);
				//modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
				lightSourceShaderProgram.setMat4("model", modelMatrix);

				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
			else 
			{
				lightSourceShaderProgram.setVec3("lightSourceColor", glm::vec3(0.0f, 0.0f, 0.0f));
				glm::mat4 modelMatrix = glm::mat4(1.0f);
				modelMatrix = glm::translate(modelMatrix, lightSourcePositions[i]);
				//modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
				lightSourceShaderProgram.setMat4("model", modelMatrix);

				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
			
		}

		


		glDisable(GL_DEPTH_TEST);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glEnable(GL_DEPTH_TEST);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
