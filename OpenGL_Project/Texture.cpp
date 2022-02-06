#include"Texture.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum colorFormat, GLenum pixelType)
{
	type = texType;
	
	int widthImg, heightImg, numColch;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColch, 0);

	//Generate textures in this case, the number is 1
	glGenTextures(1, &ID);
	//When OpenGL generates textures, it generates texture units, not just a texture, so that we have to activate a texture unit which we want to bind
	glActiveTexture(slot);
	//Bind the target texture form to our texture
	glBindTexture(texType, ID);

	//glTexParameter is the only way we can change texture setting. 
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, colorFormat, pixelType, bytes);
	glGenerateMipmap(texType);

	stbi_image_free(bytes);
	glBindTexture(texType, 0);
}

void Texture::TexUnit(Shader& shader, const char* uniform, GLuint unit)
{
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	shader.Activate();
	glUniform1i(texUni, 0);
}

void Texture::Bind()
{
	glBindTexture(type, ID);
}

void Texture::Unbind()
{
	glBindTexture(type, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}

