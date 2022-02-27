#ifndef VAO_H_CLASS
#define VAO_H_CLASS

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "VBO.h"

class VAO
{
	public:
		GLuint ID;

		VAO();

		void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);

		void Bind();
		void Unbind();
		void Delete();
};

#endif // !VAO_H_CLASS
