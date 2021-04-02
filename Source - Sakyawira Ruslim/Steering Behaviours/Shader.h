/***********************
  File Name   :   Shader.h
  Description :   declare the Shader class which contains the program and control the uniform of an object
  Author      :   Sakyawira Nanda Ruslim
  Mail        :   Sakyawira@gmail.com
********************/
#pragma once
#include <vector>
#include <glew.h>
#include <gtc/type_ptr.hpp>
#include "ShaderLoader.h"
#include "Texture.h"

class Shader
{
public:
	Shader(const char* _vertexShaderFilename, const char* _fragmentShaderFilename);
	~Shader() = default;
	void Transform(glm::mat4 _translationMatrix, glm::mat4 _rotationZ, glm::mat4 _scaleMatrix, glm::mat4 _modelMatrix);
	void PassTexture(std::vector<Texture*> _textures);
	void PassUniform(const GLchar* _name, GLfloat _float);
	void PassUniform(const GLchar * _name, GLint _int);
	void Activate();
	GLuint GetProgram();

private:
	GLuint program;
};

