/***********************
  Bachelor of Software Engineering
  Media Design School
  Auckland
  New Zealand

  (c) 2018 Media Design School

  File Name   :   GameObject.h
  Description :   contains declaration of GameObject class which control the updates and drawing pipeline of an object
  Author      :   Sakyawira Nanda Ruslim
  Mail        :   Sakyawira.Rus8080@mediadesign.school.nz
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
#define	MOVE_UP      0
#define	MOVE_DOWN    1
#define MOVE_RIGHT   2
#define	MOVE_LEFT    3

// Used for returning coordinates
typedef std::pair<float, float> Coordinate;

// Coordinate identifiers
#define TOP			0
#define BOTTOM		1
#define LEFT		2
#define RIGHT		3


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

		bool m_currently_moved = false;
	
	protected:

	
	
		// Enable Drawing
		bool m_bool_enable = true;
		
		// Shader
		Shader* m_shader;
	
		// Mesh
		Mesh* m_mesh;
	
		// Camera
		/*Camera m_camera;*/
		
		// Texture Vector
		std::vector<Texture*> m_textures;
	
		// Position
		float m_xPos = 200.0f;
		float m_yPos = 200.0f;
	
		// Scale
		float m_scale = 1.0f;
		
		// Translation Matrix
		glm::vec3 m_objPosition = glm::vec3(m_xPos, m_yPos, 0.0f);
		glm::mat4 m_translationMatrix = glm::translate(glm::mat4(), m_objPosition);
	
		// Rotation
		glm::vec3 m_rotationAxisZ = glm::vec3(0.0f, 0.0f, 1.0f);
		float m_rotationAngle = 0.0f;
		glm::mat4 m_rotationZ = glm::rotate(glm::mat4(), glm::radians(m_rotationAngle), m_rotationAxisZ);
	
		// Scaling 
		glm::vec3 m_objScale = glm::vec3(1.0f * m_scale, 1.0f * m_scale, 0.0f);
		glm::mat4 m_scaleMatrix = glm::scale(glm::mat4(), m_objScale);
	
		// Model matrix
		glm::mat4 m_modelMatrix = m_translationMatrix * m_rotationZ * m_scaleMatrix;
	
		// Vertices
		
};
