/***********************
  File Name   :   ShaderLoader.h
  Description :   Contains declaration of a singleton helper class that loads shaders and attach them to a program
  Author      :   Sakyawira Nanda Ruslim
  Mail        :   Sakyawira@gmail.com
********************/
#pragma once
// Dependency Includes
#include <glew.h>
#include <freeglut.h>

// Library Includes
#include <iostream>
#include <string>
#include <map>

class ShaderLoader
{
public:
	static ShaderLoader& GetInstance();
	ShaderLoader(ShaderLoader const&) = delete;
	void operator=(ShaderLoader const&) = delete;
	static GLuint CreateProgram(const char* _vertexShaderFilename, const char* _fragmentShaderFilename);

private:
	ShaderLoader() {}
	~ShaderLoader() {}
	static GLuint createShader(GLenum _shaderType, const char* _shaderName);
	static std::string readShaderFile(const char *_filename);
	static void printErrorDetails(bool _isShader, GLuint _id, const char* _name);

	std::map<GLuint, std::string> shaderMap;
};