/***********************
  File Name   :   Mesh.h
  Description :   contains definition of Mesh class's constructor and functions
  Author      :   Sakyawira Nanda Ruslim
  Mail        :   Sakyawira@gmail.com
********************/
#include "Mesh.h"

/***********************
 Description :   Reads the vertices as position, color, and texture
********************/
Mesh::Mesh(const std::vector<GLuint>& indices, const std::vector<GLfloat>& _vertices) :
	indicesSize(indices.size()),
	vertices(_vertices)
{
	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);

	glGenBuffers(1, &mEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	// 3 is the size of each vertex
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices.front(), GL_STATIC_DRAW);

	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	// 3 is the size of each vertex
	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(float), &_vertices.front(), GL_STATIC_DRAW);

	// Position
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),	// Stride of the single vertex (pos)
		(GLvoid*)0);			// Offset from beginning of Vertex

	glEnableVertexAttribArray(0);

	// Color
	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),	// Stride of the single vertex (pos)
		(GLvoid*)(3 * sizeof(GLfloat)));			// Offset from beginning of Vertex

	glEnableVertexAttribArray(1);


	// Texture
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
 Description :   Uses this mesh to draw the next object
********************/
void Mesh::Bind()
{
	glBindVertexArray(mVAO);
}

/***********************
 Description :   Gets the indices size
********************/
int Mesh::GetSize()
{
	return indicesSize;
}
