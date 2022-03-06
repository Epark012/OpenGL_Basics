#include "Graphics/imgui/imgui.h"
#include "Graphics/imgui/imgui_impl_glfw.h"
#include "Graphics/imgui/imgui_impl_opengl3.h"

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include "Shader.h"
#include "model.h"

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//#include <stb/stb_image.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void ProcessInput(GLFWwindow* window);

//Camera parameter
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

//Mouse Input
bool firstMouse = true;
float yaw = -90.0f;	
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 45.0f;

//Delta Time 
float deltaTime = 0.0f;
float lastFrameTime = 0.0f;

glm::vec3 lightPos(0.0f, 2.0f, 0.0f);


GLfloat vertice[] =
{
      //Bottom
      //Coordinate				 //Normal				//Color					//Tex
     -0.5f, -0.5f,	 0.5f,		 0.0f, -1.0f, 0.0f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,
	  0.5f, -0.5f,	 0.5f,		 0.0f, -1.0f, 0.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,
	  0.5f, -0.5f,	-0.5f,		 0.0f, -1.0f, 0.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,
	 -0.5f, -0.5f,	-0.5f,		 0.0f, -1.0f, 0.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f,
								 
	 //Top						 		
	 //Coordinate				 //Normal					//Color				//Tex
	 -0.5f,  0.5f,	 0.5f,		 0.0f, 1.0f, 0.0f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,
	  0.5f,  0.5f,	 0.5f,		 0.0f, 1.0f, 0.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,
	  0.5f,  0.5f,	-0.5f,		 0.0f, 1.0f, 0.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,
	 -0.5f,  0.5f,	-0.5f,		 0.0f, 1.0f, 0.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f,
								 
	 //Front					 		
	 //Coordinate				 //Normal					//Color				//Tex
	 -0.5f, -0.5f,	 0.5f,		 0.0f, 0.0f, 1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,
	  0.5f, -0.5f,	 0.5f,		 0.0f, 0.0f, 1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,
	  0.5f,  0.5f,	 0.5f,		 0.0f, 0.0f, 1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,
	 -0.5f,  0.5f,	 0.5f,		 0.0f, 0.0f, 1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f,
								 
	  //Back						 	
	  //Coordinate				 //Normal					//Color				//Tex
     -0.5f, -0.5f,	-0.5f,		 0.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,
	  0.5f, -0.5f,	-0.5f,		 0.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,
	  0.5f,  0.5f,	-0.5f,		 0.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,
     -0.5f,  0.5f,	-0.5f,		 0.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f,

	  //Right								
	  //Coordinate				//Color					//Color					//Tex
	  0.5f, -0.5f,	 0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,
	  0.5f, -0.5f,	-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,
	  0.5f,  0.5f,	-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,
	  0.5f,  0.5f,	 0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f,

     //Left							
     //Coordinate				//Color					//Color					//Tex
     -0.5f, -0.5f,	 0.5f,		-1.0f, 0.0f, 0.0f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,
     -0.5f, -0.5f,	-0.5f,		-1.0f, 0.0f, 0.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,
     -0.5f,  0.5f,	-0.5f,		-1.0f, 0.0f, 0.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,
     -0.5f,  0.5f,	 0.5f,		-1.0f, 0.0f, 0.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f
};

GLuint indices[] =
{
	0,1,2,
	0,2,3,

	4,5,6,
	4,6,7,

	8,9,10,
	8,10,11,

	12,13,14,
	12,14,15,

	16,17,18,
	16,18,19,

	20,21,22,
	20,22,23
};

GLfloat lightVertices[] =
{ //     COORDINATES     //
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};

glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  5.0f),
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

unsigned int SCREEN_WITDH = 800;
unsigned int SCREEN_HEIGHT = 600;

int main()
{
	#pragma region OpenGL Basic Set-up

	//Initialise GLFW and hint it, in this case, OpenGL version is 3.3
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	SCREEN_WITDH = mode->width;
	SCREEN_HEIGHT = mode->height;


	//Create a window and debug if there is an error
	GLFWwindow* window = glfwCreateWindow(SCREEN_WITDH, SCREEN_HEIGHT, "MODEL RENDERER PROJECT", NULL, NULL);
	if (!window)
	{
		std::cout << "ERROR::INSTANTIATE::WINDOW" << std::endl;
		glfwTerminate();
		return -1;
	}

	//Introduce the window the current context
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	//Load GLAD, call GLAD before using GLAD methods
	gladLoadGL();
	//stbi_set_flip_vertically_on_load(true);
#pragma endregion

	//Shader
	Shader shader("basic.vert", "basic.frag");

	
	//Create transformations
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	glm::mat4 projection = glm::mat4(1.0f);

	shader.Use();
	Model porori("Graphics/model/Survival_BackPack_2.fbx");

	#pragma region Lighting Cube

	//Lighting Box
	Shader lightShader("light.vert", "light.frag");
	GLuint lightVAO, lightVBO, lightEBO;
	glGenVertexArrays(1, &lightVAO);
	glGenBuffers(1, &lightVBO);
	glGenBuffers(1, &lightEBO);
	glBindVertexArray(lightVAO);

	glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lightVertices), lightVertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lightEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(lightIndices), lightIndices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	lightShader.Use();
	lightShader.SetMat4("projection", projection);
	lightShader.SetMat4("view", view);
	model = glm::mat4(1.0f);
	model = glm::translate(model, lightPos);
	model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
	lightShader.SetMat4("model", model);

	#pragma endregion
	#pragma region Framebuffer / RenderBuffer
	//Generate a frame buffer
	GLuint fbo;
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	//Generate a texture
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCREEN_WITDH, SCREEN_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//attach it  to currently bound framebuffer object
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

	GLuint rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCREEN_WITDH, SCREEN_HEIGHT);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER::FAILED_COMPLETION" << std::endl;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	#pragma endregion
	#pragma region OpenGL Scene Configuration
	//WireMode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//Depth Test
	glEnable(GL_DEPTH_TEST);
	#pragma endregion
	#pragma region imgui configuration

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	#pragma endregion



	//Main Loop
	while (!glfwWindowShouldClose(window))
	{
		//Input

		ProcessInput(window);
		
		//DeltaTime
		float currentFrameTime = glfwGetTime();
		deltaTime = currentFrameTime - lastFrameTime;
		lastFrameTime = currentFrameTime;

		//Framebuffer
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glEnable(GL_DEPTH_TEST);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//imgui 
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		//Use shader program first	
		shader.Use();

		//Camera Function
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -10.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WITDH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		shader.SetMat4("projection", projection);
		shader.SetMat4("view", view);
		shader.SetMat4("model", model);
		//shader.SetVec3("lightPos", glm::vec3(lightPos.x, lightPos.y, lightPos.z));

		porori.Draw(shader);
		glBindVertexArray(0);

		//Framebuffer
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glDisable(GL_DEPTH_TEST);

		//glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 
		glClear(GL_COLOR_BUFFER_BIT);

		// also draw the lamp object - screen
		lightShader.Use();
		lightShader.SetMat4("view", view);

		glBindVertexArray(lightVAO);
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		bool mainWindowOpen = true;
		ImGui::SetNextWindowPos(ImVec2(0,0));
		ImGui::SetNextWindowSize(ImVec2(SCREEN_WITDH * 0.75, SCREEN_HEIGHT));
		ImGui::Begin("MAIN RENDERING WINDOW", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus);
		{
			ImGui::BeginChild("Game Rendering");
			ImGui::GetWindowDrawList()->AddImage(
				(void*)texture,
				ImVec2(ImGui::GetCursorScreenPos()),
				ImVec2(ImGui::GetCursorScreenPos().x + ImGui::GetWindowSize().x,
					ImGui::GetCursorScreenPos().y + ImGui::GetWindowSize().y),
				ImVec2(0, 1),
				ImVec2(1, 0)
				);
			ImGui::EndChild();
		}
		ImGui::End();


		ImGui::SetNextWindowPos(ImVec2(SCREEN_WITDH * 0.75, 0));
		ImGui::SetNextWindowSize(ImVec2(SCREEN_WITDH * 0.25, SCREEN_HEIGHT * 0.5));
		ImGui::Begin("BASIC INFO", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
		{
			ImGui::BeginChild("Info");
			ImGui::Text("Test info 1");
			ImGui::EndChild();
		}
		ImGui::End();

		ImGui::SetNextWindowPos(ImVec2(SCREEN_WITDH * 0.75, SCREEN_HEIGHT * 0.5));
		ImGui::SetNextWindowSize(ImVec2(SCREEN_WITDH * 0.25, SCREEN_HEIGHT * 0.5));
		ImGui::Begin("Test", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
		{

		}
		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glDeleteVertexArrays(1, &lightVAO);
	glDeleteProgram(shader.ID);

	glfwTerminate();
	return 0;
}

void ProcessInput(GLFWwindow* window)
{
	float cameraSpeed = deltaTime * 2.5f;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		float xpos = static_cast<float>(xposIn);
		float ypos = static_cast<float>(yposIn);

		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			glfwSetCursorPos(window, (SCREEN_WITDH / 2), (SCREEN_HEIGHT / 2));
			firstMouse = false;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
		lastX = xpos;
		lastY = ypos;

		float sensitivity = 0.1f; // change this value to your liking
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch += yoffset;

		// make sure that when pitch is out of bounds, screen doesn't get flipped
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		glm::vec3 front;
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		cameraFront = glm::normalize(front);
	}

	else
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		firstMouse = true;
	}
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	fov -= (float)yoffset;
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 45.0f)
		fov = 45.0f;
}
