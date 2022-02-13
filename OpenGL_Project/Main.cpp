#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb/stb_image.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void ProcessInput(GLFWwindow* window);

float mixValue = 0.2f;

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

GLfloat vertice[] =
{
      //Bottom
      //Coordinate				//Color					//Tex
     -0.5f, -0.5f,	 0.5f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,	
      0.5f, -0.5f,	 0.5f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,	
      0.5f, -0.5f,	-0.5f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,	
     -0.5f, -0.5f,	-0.5f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f,	
	 							
	 //Top						
	 //Coordinate				//Color					//Tex
	 -0.5f,  0.5f,	 0.5f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,	
	  0.5f,  0.5f,	 0.5f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,	
	  0.5f,  0.5f,	-0.5f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,	
	 -0.5f,  0.5f,	-0.5f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f,	
	  							
	  //Front					
	  //Coordinate				//Color					//Tex
	 -0.5f, -0.5f,	 0.5f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,	
	  0.5f, -0.5f,	 0.5f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,	
	  0.5f,  0.5f,	 0.5f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,	
	 -0.5f,  0.5f,	 0.5f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f,	
	  							
	  //Back					
	  //Coordinate				//Color					//Tex
	 -0.5f, -0.5f,	-0.5f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,	
	  0.5f, -0.5f,	-0.5f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,	
	  0.5f,  0.5f,	-0.5f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,	
	 -0.5f,  0.5f,	-0.5f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f,	
	  							
	  //Right					
	  //Coordinate				//Color					//Tex
	  0.5f, -0.5f,	 0.5f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,	
	  0.5f, -0.5f,	-0.5f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,	
	  0.5f,  0.5f,	-0.5f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,	
	  0.5f,  0.5f,	 0.5f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f,	
	  							
	  //Left					
	  //Coordinate				//Color					//Tex
	  -0.5f, -0.5f,	 0.5f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,	
	  -0.5f, -0.5f,	-0.5f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,	
	  -0.5f,  0.5f,	-0.5f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,	
	  -0.5f,  0.5f,	 0.5f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f	
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

glm::vec3 cubePositions[] = {
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

const unsigned int SCREEN_WITDH = 800;
const unsigned int SCREEN_HEIGHT = 600;

int main()
{
	std::cout << "Hellow, OpengGL Tutorial" << std::endl;

	//Initialise GLFW and hint it, in this case, OpenGL version is 3.3
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

	//Shader

	Shader shader("default.vert", "default.frag");

	GLuint VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertice), vertice, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//Texture 0 
	GLuint texture0, texture1;
	glGenTextures(1, &texture0);
	glBindTexture(GL_TEXTURE_2D, texture0);

	//upside down
	stbi_set_flip_vertically_on_load(true);

	//Set the texture wrapping / filtering options
	//Texture Wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Texture Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//load and generate the texture image
	int width, height, nrChannels;
	unsigned char* data = stbi_load("Tile1.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout<<"ERROR::TEXTURE::LOADING_FAILED\n" << std::endl;
	}
	stbi_image_free(data);

	//Texture 1
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	//Texture Wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	//Texture Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Load and generate the texture image
	data = stbi_load("1.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "ERROR::TEXTURE::LOADING_FAILED\n" << std::endl;
	}
	stbi_image_free(data);
	
	shader.Use();
	shader.SetInt("texture0", 0);
	shader.SetInt("texture1", 1);

	//Create transformations
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	glm::mat4 projection = glm::mat4(1.0f);

	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f));
	projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WITDH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);


	//Pass the matrixes
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	//WireMode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//Depth Test
	glEnable(GL_DEPTH_TEST);


	float lastTime = 0.0f;

	//Main Loop
	while (!glfwWindowShouldClose(window))
	{
		//Input
		ProcessInput(window);

		//DeltaTime
		float currentFrameTime = glfwGetTime();
		deltaTime = currentFrameTime - lastFrameTime;
		lastFrameTime = currentFrameTime;

		glClearColor(0.2f, 0.2f, 0.2f, 0.8f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Bind Texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture1);
		
		//A valuable for Mix
		shader.SetFloat("mixValue", mixValue);

		//Use shader program first	
		shader.Use();
		
		//Camera Function

		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		shader.SetMat4("view", view);

		//Bind VAO that we want to use
		glBindVertexArray(VAO);

		for (GLuint i = 0; i < 10; i++)
		{
			float angle = 20.0f * i;
			model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			if (i % 3 == 0)
			{
				angle = glfwGetTime() * 25.0f;
			}
			model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 0.3f, 0.5f));
			shader.SetMat4("model", model);
			glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		}

		//glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		//float timeValue = glfwGetTime();
		//float offsetValue = sin(timeValue) / 2;
		//shader.SetFloat("scale", offsetValue);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
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

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		mixValue += 0.01f;
		if (mixValue >= 1.0f)
			mixValue = 1.0f;
	}	
	
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		mixValue -= 0.01f;
		if (mixValue <= 0.0f)
			mixValue = 0.0f;
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