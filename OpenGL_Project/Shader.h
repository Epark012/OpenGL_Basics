#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	GLuint ID;

	//Constructor read and build the shader
	Shader(const char* vertexPath, const char* fragmentPath);
	//Use / Activate the shader
	void Use();

	//Methods for uniform funcsions
	void SetBool(const std::string& name, bool value) const;
	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float value) const;

	void SetVec3(const std::string& name, glm::vec3 value) const;

	void SetMat3(const std::string& name, glm::mat3 &mat) const;
	void SetMat4(const std::string& name, glm::mat4 &mat) const;

private:

};

#endif // !SHADER_CLASS_H#pragma once
