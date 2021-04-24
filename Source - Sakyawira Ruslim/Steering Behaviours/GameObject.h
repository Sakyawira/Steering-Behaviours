/***********************
  File Name   :   GameObject.h
  Description :   contains declaration of GameObject class which control the position and rendering pipeline of an object
  Author      :   Sakyawira Nanda Ruslim
  Mail        :   Sakyawira@gmail.com
********************/
#pragma once
// Library Includes
#include <vector>

// Dependency Includes
#include <glew.h>
#include <gtc/type_ptr.hpp>
#include <glm.hpp>
#include <mat4x2.hpp>
//#include <gtc/matrix_transform.inl>

// Local Includes
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Camera.h"

// Move identifiers
enum class MoveDirection {
	MOVE_UP    ,
	MOVE_DOWN  ,
	MOVE_RIGHT ,
	MOVE_LEFT  
};

// Coordinate identifiers
enum class CoordinateID {
	TOP		,
	BOTTOM	,
	LEFT	,
	RIGHT	
};

class GameObject
{
	public:
		GameObject() = default;
		GameObject(Shader* _shader, Mesh* _mesh, std::vector<Texture*>&& _textures, float _initial_x, float _initial_y);
		~GameObject() = default;
	
		void Draw(Camera& _camera, const GLchar* s_currentTime, GLfloat f_currentTime);
		void Draw(Camera& _camera, const GLchar* s_currentTime, GLfloat f_currentTime, const GLchar* s_frameTime, GLint i_frameTime);

		glm::vec3 GetPosition();
		void SetPosition(float _x_pos, float _y_pos);
		float GetBoundingCoordinate(CoordinateID COORDINATE_ID);
		void Move(MoveDirection MOVE_ID, float SPEED);
		float GetScale();
		void Scale(float _scale);
		void Enable();
		void Disable();

		bool CurrentlyMoved = false;
	
	protected:
		// Enable Drawing
		bool enabled = true;
		
		Shader* shader = nullptr;
		Mesh* mesh = nullptr;
		std::vector<Texture*> textures;
	
		// Position
		float xPos = 200.0f;
		float yPos = 200.0f;
	
		// Scale
		float scale = 1.0f;
		
		// Translation Matrix
		glm::vec3 objPosition = glm::vec3(xPos, yPos, 0.0f);
		glm::mat4 translationMatrix = glm::translate(glm::mat4(), objPosition);
	
		// Rotation
		glm::vec3 rotationAxisZ = glm::vec3(0.0f, 0.0f, 1.0f);
		float rotationAngle = 0.0f;
		glm::mat4 rotationZ = glm::rotate(glm::mat4(), glm::radians(rotationAngle), rotationAxisZ);
	
		// Scaling 
		glm::vec3 objScale = glm::vec3(1.0f * scale, 1.0f * scale, 0.0f);
		glm::mat4 scaleMatrix = glm::scale(glm::mat4(), objScale);
	
		// Model matrix
		glm::mat4 modelMatrix = translationMatrix * rotationZ * scaleMatrix;
};
