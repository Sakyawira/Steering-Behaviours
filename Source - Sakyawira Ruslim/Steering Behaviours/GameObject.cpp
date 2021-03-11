/***********************
  Bachelor of Software Engineering
  Media Design School
  Auckland
  New Zealand

  (c) 2018 Media Design School

  File Name   :   GameObject.h
  Description :   contains definition of GameObject class which control the updates and drawing pipeline of an object
  Author      :   Sakyawira Nanda Ruslim
  Mail        :   Sakyawira.Rus8080@mediadesign.school.nz
********************/
#include "GameObject.h"

GameObject::GameObject(Shader* _shader, Mesh* _mesh, std::vector<Texture*>& _textures, float _initial_x, float _initial_y)
{
	m_shader = _shader;
	m_mesh = _mesh;
	m_xPos = _initial_x;
	m_yPos = _initial_y;
	// This creates a copy (even though was passed a s a reference) and therefore did not work
	// m_camera = _camera;
	m_textures = _textures;

	m_objPosition = glm::vec3(m_xPos, m_yPos, 0.0f);
	m_translationMatrix = glm::translate(glm::mat4(), m_objPosition);
	m_modelMatrix = m_translationMatrix * m_rotationZ * m_scaleMatrix;
}

void GameObject::Draw(Camera& _camera, const GLchar* s_currentTime, GLfloat f_currentTime)
{
	if (m_bool_enable)
	{
		m_shader->Activate();

		m_shader->PassUniform(s_currentTime, f_currentTime);

		// Passing texture to 'program'
		m_shader->PassTexture(m_textures);

		// Transform the objects controlled by 'program'
		m_shader->Transform(m_translationMatrix, m_rotationZ, m_scaleMatrix, m_modelMatrix);

		// So it uses the reference and not a copy
		_camera.CameraUpdate();

		// Using camera on the program
		_camera.UseCamera(m_shader->GetProgram());

		// Hexagon 1
		m_mesh->Bind();
		glDrawElements(GL_TRIANGLES, m_mesh->GetSize(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}

void GameObject::Draw(Camera & _camera, const GLchar * s_currentTime, GLfloat f_currentTime, const GLchar * s_frameTime, GLint i_frameTime)
{
	if (m_bool_enable)
	{
		m_shader->Activate();

		m_shader->PassUniform(s_currentTime, f_currentTime);

		m_shader->PassFrameUniform(s_frameTime, i_frameTime);

		// Passing texture to 'program'
		m_shader->PassTexture(m_textures);

		// Transform the objects controlled by 'program'
		m_shader->Transform(m_translationMatrix, m_rotationZ, m_scaleMatrix, m_modelMatrix);

		// So it uses the reference and not a copy
		_camera.CameraUpdate();

		// Using camera on the program
		_camera.UseCamera(m_shader->GetProgram());

		// Hexagon 1
		m_mesh->Bind();
		glDrawElements(GL_TRIANGLES, m_mesh->GetSize(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}

void GameObject::SetPosition(float _x_pos, float _y_pos)
{
	m_xPos = _x_pos;
	m_yPos = _y_pos;

	m_objPosition = glm::vec3(m_xPos, m_yPos, 0.0f);
	m_translationMatrix = glm::translate(glm::mat4(), m_objPosition);
	m_modelMatrix = m_translationMatrix * m_rotationZ * m_scaleMatrix;
}

float GameObject::GetPosition(int COORDINATE_ID)
{
	// float fi;
	if (COORDINATE_ID == TOP)
	{
		return (m_yPos + m_scale/2);
		//fi = m_mesh->GetVertices().at(1);
	}
	else if (COORDINATE_ID == BOTTOM)
	{
		return (m_yPos - m_scale / 2);
	}
	else if (COORDINATE_ID == LEFT)
	{
		return (m_xPos - m_scale /2);
	}
	else if (COORDINATE_ID == RIGHT)
	{
		return (m_xPos + m_scale / 2);
	}
	else
	{
		return 0.0f;
	}
	// std::cout << fi;
}

glm::vec3 GameObject::GetLocation()
{
	return m_objPosition;
}

void GameObject::Move(int MOVE_ID, float SPEED)
{
	float xSpeed = 0.0f;
	float ySpeed = 0.0f;
	
	if (MOVE_ID == MOVE_UP)
	{
		ySpeed += SPEED;
		m_yPos += SPEED;
	}
	if (MOVE_ID == MOVE_DOWN)
	{
		ySpeed -= SPEED;
		m_yPos -= SPEED;
	}
	if (MOVE_ID == MOVE_RIGHT)
	{
		xSpeed += SPEED;
		m_xPos += SPEED;
	}
	if (MOVE_ID == MOVE_LEFT)
	{
		xSpeed -= SPEED;
		m_xPos -= SPEED;
	}

	m_objPosition += (glm::normalize(glm::vec3(xSpeed, ySpeed, 0.0f))* SPEED);
	//m_objPosition = glm::normalize(m_objPosition) * SPEED;
	m_translationMatrix = glm::translate(glm::mat4(), m_objPosition);
	m_modelMatrix = m_translationMatrix * m_rotationZ * m_scaleMatrix;
}

float GameObject::GetScale()
{
	return m_scale;
}

void GameObject::Scale(float _scale)
{
	m_scale = _scale;
	m_objScale = glm::vec3(1.0f * m_scale, 1.0f * m_scale, 0.0f);
	m_scaleMatrix = glm::scale(glm::mat4(), m_objScale);
	m_modelMatrix = m_translationMatrix * m_rotationZ * m_scaleMatrix;
}

void GameObject::Enable()
{
	m_bool_enable = true;
}

void GameObject::Disable()
{
	m_bool_enable = false;
}

