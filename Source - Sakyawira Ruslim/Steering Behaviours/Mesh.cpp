/***********************
  File Name   :   Mesh.h
  Description :   contains definition of Mesh class's constructor and functions
  Author      :   Sakyawira Nanda Ruslim
  Mail        :   Sakyawira@gmail.com
********************/
#include "Mesh.h"

/***********************
 Description :   Loads main scene and activates loading screen
********************/
Mesh::Mesh(const std::vector<GLuint>& indices, const std::vector<GLfloat>& vertices)
{
	m_indicesSize = indices.size();

	m_vertices = vertices;

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	// 3 is the size of each vertex
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices.front(), GL_STATIC_DRAW);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	// 3 is the size of each vertex
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices.front(), GL_STATIC_DRAW);

	/// Position
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),	// Stride of the single vertex (pos)
		(GLvoid*)0);			// Offset from beginning of Vertex

	glEnableVertexAttribArray(0);

	/// Color
	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),	// Stride of the single vertex (pos)
		(GLvoid*)(3 * sizeof(GLfloat)));			// Offset from beginning of Vertex

	glEnableVertexAttribArray(1);


	/// Texture
	glVertexAttribPointer(
		2,
		2,									// 2 float components for coordinates 
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),				// Stride the single vertex (pos + color + tex)
		(GLvoid*)(6 * sizeof(GLfloat)));	// offset from beginning of Vertex
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}

/***********************
 Description :   Loads main scene and activates loading screen
********************/
void Mesh::Bind()
{
	glBindVertexArray(m_VAO);
}

/***********************
 Description :   Loads main scene and activates loading screen
********************/
int Mesh::GetSize()
{
	return m_indicesSize;
}

/***********************
 Description :   Loads main scene and activates loading screen
********************/
std::vector<GLfloat> Mesh::GetVertices()
{
	return m_vertices;
}
