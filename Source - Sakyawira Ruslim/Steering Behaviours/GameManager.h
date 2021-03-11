/***********************
  Bachelor of Software Engineering
  Media Design School
  Auckland
  New Zealand

  (c) 2018 Media Design School

  File Name   :   GameObject.h
  Description :   contains declaration of GameManager class which control the gameplay, rendering of all game objects
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
#include "Vehicle.h"
#include "TextLabel.h"
#include "clock.h"
#include "Audio.h"


const int WINDOW_WIDHT = 800;
const int WINDOW_HEIGHT = 800;

class GameManager
{
public:
	GameManager();
	~GameManager();

	void Initialize();
	
	void ProcessGame(Audio& audio, glm::vec3 mouse_location);

	float g_player_size = 1;

	bool collision_check(float _top, float _bottom, float _left, float _right);

	void Enemy_Collision_Check();

	void Enemy_Collision_Check2();

	void Render();

	bool IsStarted();

	bool IsEnded();

	void StartGame();

	void set_behaviour(behaviour steer);

	void change_behaviour_text();

	CClock* GetClock();

	GameObject* player;
	Camera camera;
	
private:

	// Enum for behaviour type
	behaviour m_steering = SEEK;
	
	// Clock
	CClock* m_clock;

	// Check whether or not m_program has been initialized
	bool m_b_initialized = false;
	
	// Control whether the game has been started
	bool m_b_start = false;
	bool m_b_ended = false;
	
	// Declaring Strings
	int m_i_steer = 0;
	std::string m_string_steer;
	TextLabel* m_text_steer;

	// Menu Text
	std::string m_string_menu = "Sakyawira's Burnt Out";
	TextLabel* m_text_menu;

	// Instruction Text
	std::string m_string_instruction = "Press 'R' to start the game...";
	TextLabel* m_text_instruction;

	// Uniforms
	GLfloat currentTime;
	float frameCounts = 0;

	Shader* m_sh_alternating;
	Shader* m_sh_animate;
	Shader* m_sh_scroll;

	Texture* m_tr_stars;
	Texture* m_tr_background;
	Texture* m_tr_slimes;
	Texture* m_tr_water;
	Texture* m_tr_menu;

	Mesh* m_mesh_animate;
	Mesh* m_mesh_animate2;
	Mesh* m_mesh_scroll;
	Mesh* m_mesh_player;
	Mesh* m_mesh_static;

	Vehicle* m_enemy_ice;
	Vehicle* m_enemy_earth;

	GameObject* wall;
	GameObject *Menu;
	GameObject* background;

	// Vectors
	std::vector<Vehicle*> m_vector_enemyEarth;
	std::vector<Vehicle*> m_vector_enemyIce;
	std::vector<GameObject*> m_vector_obstacleObjects;
	std::vector<GameObject*> m_vector_backgroundObjects;
	std::vector<GameObject*> m_vector_playerObjects;
	std::vector<Vehicle*> m_vector_erasedEarth;
	std::vector<Vehicle*> m_vector_erasedIce;

	std::vector<GLfloat> static_vertices =
	{
		// Position				// Color			// Texture Coords
		-0.5f,  0.5f, 0.0f,		0.0f, 1.0f,	1.0f,	0.0f, 0.0f,			// Top-Left
		 0.5f,  0.5f, 0.0f,		0.0f, 0.0f,	1.0f,	1.0f, 0.0f,			// Top-Right
		-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	0.0f, 1.0f,			// Bottom-Left
		 0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f,			// Bottom-Right
	};

	std::vector<GLfloat> player_animation_vertices =
	{
		// Position				// Color			// Texture Coords
		-0.5f,  0.5f, 0.0f,		0.0f, 1.0f,	1.0f,	0.0f, 0.001f,		// Top-Left
		 0.5f,  0.5f, 0.0f,		0.0f, 0.0f,	1.0f,	0.125f, 0.001f,		// Top-Right
		-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	0.0f, 0.2f,			// Bottom-Left
		 0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	0.125f, 0.2f,		// Bottom-Right
	};

	std::vector<GLfloat> enemy2_vertices =
	{
		// Position				// Color			// Texture Coords
		-0.5f,  0.5f, 0.0f,		0.0f, 1.0f,	1.0f,	0.0f, 0.2f,			// Top-Left
		 0.5f,  0.5f, 0.0f,		0.0f, 0.0f,	1.0f,	0.125f, 0.2f,		// Top-Right
		-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	0.0f, 0.4f,			// Bottom-Left
		 0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	0.125f, 0.4f,		// Bottom-Right
	};

	// Animation has 4 textures in one image
	std::vector<GLfloat> animation_vertices =
	{
		// Position				// Color			// Texture Coords
		-0.5f,  0.5f, 0.0f,		0.0f, 1.0f,	1.0f,	0.0f, 0.4f,			// Top-Left
		 0.5f,  0.5f, 0.0f,		0.0f, 0.0f,	1.0f,	0.125f, 0.4f,		// Top-Right
		-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	0.0f, 0.6f,			// Bottom-Left
		 0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	0.125f, 0.6f,		// Bottom-Right
	};

	std::vector<GLfloat> water_scrolling_vertices =
	{
		// Position				// Color			// Texture Coords
		-0.5f,  0.5f, 0.0f,		0.0f, 1.0f,	1.0f,	0.0f, 0.4f,			// Top-Left
		 0.5f,  0.5f, 0.0f,		0.0f, 0.0f,	1.0f,	1.0f, 0.4f,			// Top-Right
		-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	0.0f, 0.6f,			// Bottom-Left
		 0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	1.0f, 0.6f,			// Bottom-Right
	};

	// indices reuses the four unique values to create shapes
	std::vector<GLuint> indicesVector =
	{
		0, 4, 3,
		0, 1, 2, // First Triangle
		2, 3, 0, // Second Triangle
		1, 5, 2,
	};

	std::vector<GLuint> animation_indices =
	{
		1, 2, 3, // First Triangle
		1, 0, 2, // Second Triangle
	};
};

