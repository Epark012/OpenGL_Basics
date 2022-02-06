#include<iostream>
#include<glad/glad.h>
#include<glfw/glfw3.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Texture.h"
#include"Camera.h"

#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

//Triangle info
//Vertices Coordinates 
GLfloat vertices[] =
{
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
};

GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};

//Square info
GLfloat sqrVertices[] =
{
	//Coordinates		 //Colors
	-0.5f, -0.5f, 0.0f,    1.0f, 0.0f, 0.0f,	0.0f, 0.0f,	//Lower Left
	-0.5f,  0.5f, 0.0f,    0.0f, 1.0f, 0.0f,	0.0f, 1.0f,	//Upper Left
	 0.5f,  0.5f, 0.0f,    0.0f, 0.0f, 1.0f,	1.0f, 1.0f,	//Upper Right
	 0.5f, -0.5f, 0.0f,    1.0f, 1.0f, 1.0f,	1.0f, 0.0f	//Lower Right
};

GLuint sqrIndices[] =
{
	3, 2, 1, //Upper
	1, 0, 3
};

//Cube Vertices
GLfloat cubeVertices[] =
{
	//Coordinates		//Color				Texture
	-0.5f, -0.5f,  0.5f,	0.5f, 0.2f, 0.1f,	0.0f, 0.0f, //Lower
	 0.5f, -0.5f,  0.5f,	0.5f, 0.2f, 0.1f,	0.0f, 1.0f, //Lower
	 0.5f, -0.5f, -0.5f,	0.5f, 0.2f, 0.1f,	1.0f, 1.0f,	//Lower
	-0.5f, -0.5f, -0.5f,	0.5f, 0.2f, 0.1f,	1.0f, 0.0f,	//Lower
	-0.5f,  0.5f,  0.5f,	0.1f, 0.5f, 0.7f,	0.0f, 0.0f, //Upper
	 0.5f,  0.5f,  0.5f,	0.1f, 0.5f, 0.7f,	0.0f, 1.0f,	//Upper
	-0.5f,  0.5f, -0.5f,	0.1f, 0.5f, 0.7f,	1.0f, 1.0f,	//Upper
	 0.5f,  0.5f, -0.5f,	0.1f, 0.5f, 0.7f,	1.0f, 0.0f	//Upper
};

GLuint cubeIndices[] =
{
	0, 1, 2, // Bottom
	0, 2, 3,
	4, 5, 6, // Top
	4, 6, 7,
	0, 1, 5, // Front
	0, 5, 4,
	1, 2, 6, //Right
	1, 6, 5,
	2, 3, 7, //Back
	2, 7, 6,
	0, 3, 7, //Left
	0, 3, 4
};

const unsigned int width = 800;
const unsigned int height = 800;

int main()
{
	//Initialise GLFW
	glfwInit();

	//Tell GLFW what version of OpenGL we are using 
	//In this case, we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	
	//Tell GLFW we are using the CORE profile
	//so that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Create a window of 800 by 800 pixels, naming it OpenGL Project
	GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL Project", NULL, NULL);

	//Error Check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to Create GLFW Window" << std::endl;
		glfwTerminate();
		return -1;
	}

	//Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();

	//Specify the viewport of OpenGL in the window
	//In this case, the viewport goes from x = 0, y = 0 to x = 800, y = 800
	glViewport(0, 0, width, height);

	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8	* sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8	* sizeof(float), (void*)(3*sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8	* sizeof(float), (void*)(6*sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	//Texture
	Texture adobeImg = Texture("1.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	adobeImg.TexUnit(shaderProgram, "tex0", 0);

	glEnable(GL_DEPTH_TEST);

	//Camera

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	//Main while loop
	while(!glfwWindowShouldClose(window))
	{

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();

		camera.Inputs(window);

		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "cameraMat");

		//Texture
		adobeImg.Bind();
		//Bind the VAO so OpenGL knows to use it 
		VAO1.Bind();
		//Draw the triangle using GL_TRIANGLES
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);	

		//Take care of all GLFW events
		glfwPollEvents();
	}

	//Delete all the objects we created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	adobeImg.Delete();

	shaderProgram.Delete();

	//Delete window before ending the program
	glfwDestroyWindow(window);
	//Terminating GLFW before ending the program
	glfwTerminate();

	return 0;
}