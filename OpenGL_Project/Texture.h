#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include<stb/stb_image.h>
#include<glad/glad.h>
#include<string>

#include"shaderClass.h"

class Texture 
{
	public:
		GLuint ID;
		const char* type;
		GLuint unit;
		std::string path;
		
		Texture();
		Texture(const char* image, const char* texType, GLuint slot, GLenum format, GLenum pixelType);

		void texUnit(Shader& shader, const char* uniform, GLuint unit);
		void Bind();
		void Unbind();
		void Delete();
};

#endif