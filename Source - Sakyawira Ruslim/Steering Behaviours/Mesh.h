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
	//Square 1
public:
	Mesh(const std::vector<GLuint>& indices, const std::vector<GLfloat>& vertices);
	~Mesh() = default;

	void Bind();
	int GetSize();

	std::vector<GLfloat> GetVertices();

private:

	GLuint m_VAO{0};
	GLuint m_EBO{0};
	GLuint m_VBO{0};

	// These are copies, they can not be used to control the actual one
	std::vector<GLfloat> m_vertices;
	int m_indicesSize;
};
