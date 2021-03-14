/***********************
  File Name   :   GameObject.cpp
  Description :   contains definition of GameObject class which control the position and rendering pipeline of an object
  Author      :   Sakyawira Nanda Ruslim
  Mail        :   Sakyawira@gmail.com
********************/
#include "GameObject.h"

GameObject::GameObject(Shader* _shader, Mesh* _mesh, std::vector<Texture*>& _textures, float _initial_x, float _initial_y)
{
	shader = _shader;
	mesh = _mesh;
	xPos = _initial_x;
	yPos = _initial_y;
	// This creates a copy (even though was passed a s a reference) and therefore did not work
	// m_camera = _camera;
	textures = _textures;

	objPosition = glm::vec3(xPos, yPos, 0.0f);
	translationMatrix = glm::translate(glm::mat4(), objPosition);
	modelMatrix = translationMatrix * rotationZ * scaleMatrix;
}

void GameObject::Draw(Camera& _camera, const GLchar* s_currentTime, GLfloat f_currentTime)
{
	if (enable)
	{
		shader->Activate();

		shader->PassUniform(s_currentTime, f_currentTime);

		// Passing texture to 'program'
		shader->PassTexture(textures);

		// Transform the objects controlled by 'program'
		shader->Transform(translationMatrix, rotationZ, scaleMatrix, modelMatrix);

		// So it uses the reference and not a copy
		_camera.CameraUpdate();

		// Using camera on the program
		_camera.UseCamera(shader->GetProgram());

		// Hexagon 1
		mesh->Bind();
		glDrawElements(GL_TRIANGLES, mesh->GetSize(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}

void GameObject::Draw(Camera & _camera, const GLchar * s_currentTime, GLfloat f_currentTime, const GLchar * s_frameTime, GLint i_frameTime)
{
	if (enable)
	{
		shader->Activate();

		shader->PassUniform(s_currentTime, f_currentTime);

		shader->PassFrameUniform(s_frameTime, i_frameTime);

		// Passing texture to 'program'
		shader->PassTexture(textures);

		// Transform the objects controlled by 'program'
		shader->Transform(translationMatrix, rotationZ, scaleMatrix, modelMatrix);

		// So it uses the reference and not a copy
		_camera.CameraUpdate();

		// Using camera on the program
		_camera.UseCamera(shader->GetProgram());

		// Hexagon 1
		mesh->Bind();
		glDrawElements(GL_TRIANGLES, mesh->GetSize(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}

void GameObject::SetPosition(float _x_pos, float _y_pos)
{
	xPos = _x_pos;
	yPos = _y_pos;

	objPosition = glm::vec3(xPos, yPos, 0.0f);
	translationMatrix = glm::translate(glm::mat4(), objPosition);
	modelMatrix = translationMatrix * rotationZ * scaleMatrix;
}

float GameObject::GetPosition(int COORDINATE_ID)
{
	// float fi;
	if (COORDINATE_ID == TOP)
	{
		return (yPos + scale/2);
		//fi = m_mesh->GetVertices().at(1);
	}
	else if (COORDINATE_ID == BOTTOM)
	{
		return (yPos - scale / 2);
	}
	else if (COORDINATE_ID == LEFT)
	{
		return (xPos - scale /2);
	}
	else if (COORDINATE_ID == RIGHT)
	{
		return (xPos + scale / 2);
	}
	else
	{
		return 0.0f;
	}
	// // std::cout << fi;
}

glm::vec3 GameObject::GetLocation()
{
	return objPosition;
}

void GameObject::Move(int MOVE_ID, float SPEED)
{
	float xSpeed = 0.0f;
	float ySpeed = 0.0f;
	
	if (MOVE_ID == MOVE_UP)
	{
		ySpeed += SPEED;
		yPos += SPEED;
	}
	if (MOVE_ID == MOVE_DOWN)
	{
		ySpeed -= SPEED;
		yPos -= SPEED;
	}
	if (MOVE_ID == MOVE_RIGHT)
	{
		xSpeed += SPEED;
		xPos += SPEED;
	}
	if (MOVE_ID == MOVE_LEFT)
	{
		xSpeed -= SPEED;
		xPos -= SPEED;
	}

	objPosition += (glm::normalize(glm::vec3(xSpeed, ySpeed, 0.0f))* SPEED);
	//m_objPosition = glm::normalize(m_objPosition) * SPEED;
	translationMatrix = glm::translate(glm::mat4(), objPosition);
	modelMatrix = translationMatrix * rotationZ * scaleMatrix;
}

float GameObject::GetScale()
{
	return scale;
}

void GameObject::Scale(float _scale)
{
	scale = _scale;
	objScale = glm::vec3(1.0f * scale, 1.0f * scale, 0.0f);
	scaleMatrix = glm::scale(glm::mat4(), objScale);
	modelMatrix = translationMatrix * rotationZ * scaleMatrix;
}

void GameObject::Enable()
{
	enable = true;
}

void GameObject::Disable()
{
	enable = false;
}

