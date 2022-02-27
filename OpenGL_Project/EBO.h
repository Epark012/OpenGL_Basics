#ifndef EBO_H_CLASS
#define EBO_H_CLASS

#include <glad/glad.h>
#include <vector>

class EBO
{
	public:	
		
		GLuint ID;
		EBO(std::vector<GLuint> indices);

		void Bind();
		void Unbind();
		void Delete();
};


#endif // !EBO_H_CLASS
