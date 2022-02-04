#include<iostream>
#include<glad/glad.h>
#include<glfw/glfw3.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

//Fragment Shader Source Code

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
	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL Project", NULL, NULL);

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
	glViewport(0, 0, 800, 800);

	//Vertices Coordinates 
	GLfloat vertices[] =
	{
		//Coordinates											//Colors			//
		-0.5f,		-0.5f * float(sqrt(3)) / 3,		0.0f,		0.3f, 1.0f, 1.0f,	//Lower Left
		 0.5f,		-0.5f * float(sqrt(3)) / 3,		0.0f,		0.7f, 1.0f, 1.0f,	//Lower Right
		 0.0f,		 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,		0.7f, 0.3f, 0.5f,	//Upper Center
		-0.5f / 2,	 0.5f * float(sqrt(3)) /		6, 0.0f,	0.0f, 0.0f, 0.0f,	//Inner Left
		 0.5f / 2,	 0.5f * float(sqrt(3)) /		6, 0.0f,	0.0f, 0.0f, 0.0f,	//Inner Rightt
		 0.0f,		-0.5f * float(sqrt(3)) /		3, 0.0f,	0.1f, 1.0f, 1.0f	//Lower Right
	};

	GLuint indices[] =
	{
		0, 3, 5,	//Lower Left Triangle
		3, 2, 4,	//Lower Right Triangle
		5, 4, 1		//Upper Triangle
	};


	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6*sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6*sizeof(float), (void*)(3*sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	//Main while loop
	while(!glfwWindowShouldClose(window))
	{

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		glUniform1f(uniID, 0.5f);
		//Bind the VAO so OpenGL knows to use it 
		VAO1.Bind();
		//Draw the triangle using GL_TRIANGLES
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);	

		//Take care of all GLFW events
		glfwPollEvents();
	}

	//Delete all the objects we created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();

	shaderProgram.Delete();

	//Delete window before ending the program
	glfwDestroyWindow(window);
	//Terminating GLFW before ending the program
	glfwTerminate();

	return 0;
}