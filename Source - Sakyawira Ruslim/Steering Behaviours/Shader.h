/***********************
  File Name   :   Shader.h
  Description :   declare the Shader class which contains the program and control the uniform of an object
  Author      :   Sakyawira Nanda Ruslim
  Mail        :   Sakyawira@gmail.com
********************/
#pragma once
#include <glew.h>
#include <vector>
#include <gtc/type_ptr.hpp>
#include "ShaderLoader.h"
#include "Texture.h"

class Shader
{
	//Square 1
public:
	Shader(const char* VertexShaderFilename, const char* FragmentShaderFilename);
	~Shader() = default;
	void Transform(glm::mat4 translationMatrix, glm::mat4 rotationZ, glm::mat4 scaleMatrix, glm::mat4 modelMatrix);
	void PassTexture(Texture* v_texture);
	void PassTexture(std::vector<Texture*> v_texture);
	void PassUniform(const GLchar* name, GLfloat _float);
	void PassFrameUniform(const GLchar * name, GLint _int);
	void Activate();
	GLuint GetProgram();

private:
	GLuint m_program;
	
};

