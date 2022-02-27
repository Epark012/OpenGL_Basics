#ifndef VBO_H_CLASS
#define VBO_H_CLASS

#include <glad/glad.h>
#include <vector>


class VBO
{
public:

	//Reference int of VBO
	GLuint ID;

	VBO(std::vector<GLfloat>);

	void Bind();
	void Unbind();
	void Delete();
};

#endif // !VBO_H_CLASS
