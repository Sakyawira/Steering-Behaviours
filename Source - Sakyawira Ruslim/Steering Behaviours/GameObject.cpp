/***********************
  File Name   :   GameObject.cpp
  Description :   contains definition of GameObject class which control the position and rendering pipeline of an object
  Author      :   Sakyawira Nanda Ruslim
  Mail        :   Sakyawira@gmail.com
********************/
#include "GameObject.h"

/***********************
 Description :   assign the shaders, mesh, and textures of the object, initialise its position
********************/
GameObject::GameObject(Shader* _shader, Mesh* _mesh, std::vector<Texture*>&& _textures, float _initial_x, float _initial_y)
{
	shader = _shader;
	mesh = _mesh;
	textures = _textures;

	xPos = _initial_x;
	yPos = _initial_y;

	objPosition = glm::vec3(xPos, yPos, 0.0f);
	translationMatrix = glm::translate(glm::mat4(), objPosition);
	modelMatrix = translationMatrix * rotationZ * scaleMatrix;
}

/***********************
 Description :   Draw the object to the scene, takes one uniform
********************/
void GameObject::Draw(Camera& _camera, const GLchar* s_currentTime, GLfloat f_currentTime)
{
	if (enabled)
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

/***********************
 Description :   Draws an animated object (this) to the scene, takes two uniforms
********************/
void GameObject::Draw(Camera & _camera, const GLchar * s_currentTime, GLfloat f_currentTime, const GLchar * s_frameTime, GLint i_frameTime)
{
	if (enabled)
	{
		shader->Activate();

		shader->PassUniform(s_currentTime, f_currentTime);

		shader->PassUniform(s_frameTime, i_frameTime);

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

/***********************
 Description :   Sets the posiion of this game object
********************/
void GameObject::SetPosition(float _x_pos, float _y_pos)
{
	xPos = _x_pos;
	yPos = _y_pos;

	objPosition = glm::vec3(xPos, yPos, 0.0f);
	translationMatrix = glm::translate(glm::mat4(), objPosition);
	modelMatrix = translationMatrix * rotationZ * scaleMatrix;
}

/***********************
 Description :   Gets this object bounding box coordinates
********************/
float GameObject::GetBoundingCoordinate(CoordinateID COORDINATE_ID)
{	
	switch (COORDINATE_ID) {
	case CoordinateID::TOP:
		return (yPos + scale / 2);
	case CoordinateID::BOTTOM:
		return (yPos - scale / 2);
	case CoordinateID::LEFT:
		return (xPos - scale / 2);
	case CoordinateID::RIGHT:
		return (xPos + scale / 2);
	default:
		return 0.0f;
	}
}

/***********************
 Description :   Gets the position of the game object
********************/
glm::vec3 GameObject::GetPosition()
{
	return objPosition;
}

/***********************
 Description :   Move the game object based on speed (must be multiplied with delta time before passed in)
********************/
void GameObject::Move(MoveDirection MOVE_ID, float _speed)
{
	float xSpeed = 0.0f;
	float ySpeed = 0.0f;
	
	switch (MOVE_ID) {
	case MoveDirection::MOVE_UP:
		ySpeed += _speed;
		yPos += _speed;
		break;
	case MoveDirection::MOVE_DOWN:
		ySpeed -= _speed;
		yPos -= _speed;
		break;
	case MoveDirection::MOVE_RIGHT:
		xSpeed += _speed;
		xPos += _speed;
		break;
	case MoveDirection::MOVE_LEFT:
		xSpeed -= _speed;
		xPos -= _speed;
		break;
	}

	objPosition += (glm::normalize(glm::vec3(xSpeed, ySpeed, 0.0f))* _speed);
	translationMatrix = glm::translate(glm::mat4(), objPosition);
	modelMatrix = translationMatrix * rotationZ * scaleMatrix;
}

/***********************
 Description :   Gets the scale of the object
********************/
float GameObject::GetScale()
{
	return scale;
}

/***********************
 Description :   Scale the object
********************/
void GameObject::Scale(float _scale)
{
	scale = _scale;
	objScale = glm::vec3(1.0f * scale, 1.0f * scale, 0.0f);
	scaleMatrix = glm::scale(glm::mat4(), objScale);
	modelMatrix = translationMatrix * rotationZ * scaleMatrix;
}

/***********************
 Description :   Enables the drawing of the object
********************/
void GameObject::Enable()
{
	enabled = true;
}

/***********************
 Description :   Disables the drawing of the object
********************/
void GameObject::Disable()
{
	enabled = false;
}

