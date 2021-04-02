/***********************
  File Name   :   Mesh.h
  Description :   declare the Mesh class which contains the VAO, VBO, and EBO of an object
  Author      :   Sakyawira Nanda Ruslim
  Mail        :   Sakyawira@gmail.com
********************/
#pragma once
#include <glew.h>
#include <vector>
#include <gtc/type_ptr.hpp>

class Mesh
{
public:

	Mesh(const std::vector<GLuint>& _indices, const std::vector<GLfloat>& _vertices);
	~Mesh() = default;
	void Bind();
	int GetSize();

private:

	GLuint mVAO{0};
	GLuint mEBO{0};
	GLuint mVBO{0};

	// These are copies, they can not be used to control the actual one
	std::vector<GLfloat> vertices;
	int indicesSize;
};
