#ifndef Renderer_H_Class
#define Renderer_H_Class

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


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void ProcessInput(GLFWwindow* window);

unsigned int loadTexture(char const* path);


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

const unsigned int SCREEN_WITDH = 800;
const unsigned int SCREEN_HEIGHT = 600;

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

unsigned int loadTexture(char const* path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}


class Renderer
{
public:
	Renderer();

	void Execute();


	GLFWwindow* window;
};

#endif // !Renderer_H_Class
