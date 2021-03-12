/***********************
  File Name   :   GameObject.h
  Description :   contains declaration of GameObject class which control the updates and drawing pipeline of an object
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
enum MoveDirection {
	MOVE_UP    = 0,
	MOVE_DOWN  = 1,
	MOVE_RIGHT = 2,
	MOVE_LEFT  = 3
};

// Used for returning coordinates
typedef std::pair<float, float> Coordinate;

// Coordinate identifiers
enum CoordinateID {
	TOP		= 0,
	BOTTOM	= 1,
	LEFT	= 2,
	RIGHT	= 3
};

class GameObject
{
	public:
		GameObject() = default;
		GameObject(Shader* _shader, Mesh* _mesh, std::vector<Texture*>& _textures, float _initial_x, float _initial_y);
		~GameObject() = default;
	
		// OverLoad that takes one uniform
		void Draw(Camera& _camera, const GLchar* s_currentTime, GLfloat f_currentTime);
		// Overload that takes two uniforms
		void Draw(Camera& _camera, const GLchar* s_currentTime, GLfloat f_currentTime, const GLchar* s_frameTime, GLint i_frameTime);

		void SetPosition(float _x_pos, float _y_pos);
		float GetPosition(int COORDINATE_ID);
		glm::vec3 GetLocation();
	
		void Move(int MOVE_ID, float SPEED);

		float GetScale();
		void Scale(float _scale);
	
		void Enable();
		void Disable();

		bool currentlyMoved = false;
	
	protected:
		// Enable Drawing
		bool enable = true;
		
		// Shader
		Shader* shader;
	
		// Mesh
		Mesh* mesh;
	
		// Texture Vector
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
