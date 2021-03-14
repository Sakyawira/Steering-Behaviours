/***********************
  File Name   :   GameManager.h
  Description :   contains declaration of GameManager class which control the creation, processing, and rendering of all objects
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
#include "Vehicle.h"
#include "TextLabel.h"
#include "clock.h"
#include "Audio.h"

const int windowWidth = 720;
const int windowHeight = 720;

class GameManager
{
public:
	GameManager();
	~GameManager();

	void Initialize();
	void ProcessGame(Audio& audio, glm::vec3 mouse_location);
	bool CollisionCheck(float _top, float _bottom, float _left, float _right);
	void Render();
	bool IsStarted();
	bool IsEnded();
	void StartGame();
	void SetBehaviour(Behaviour steer);
	void ChangeBehaviourText();
	CClock* GetClock();

	GameObject* player;
	Camera* camera;
	float playerSize = 1;
	
private:

	// Enum for behaviour type
	Behaviour currentBehaviour = SEEK;
	
	// Clock
	CClock* clock;

	// Check whether or not m_program has been initialized
	bool isInitialised = false;
	
	// Control whether the game has been started
	bool isStarted = false;
	bool isEnded = false;
	
	// Declaring Strings
	int steerNumber = 0;
	std::string steerString;
	TextLabel* steerText;

	// Menu Text
	std::string menuString = "Sakyawira's Burnt Out";
	TextLabel* menuText;

	// Instruction Text
	std::string instructionString = "Press 'R' to start the game...";
	TextLabel* instructionText;

	// Uniforms
	GLfloat currentTime;
	float frameCounts = 0;

	Shader* alternatingShader;
	Shader* animateShader;
	Shader* scrollingShader;

	Texture* starsTexture;
	Texture* backgroundTexture;
	Texture* slimesTexture;
	Texture* waterTexture;
	Texture* menuTexture;

	Mesh* vehicleGreenMesh;
	Mesh* vehicleBlueMesh;
	Mesh* waterMesh;
	Mesh* playerMesh;
	Mesh* staticMesh;

	Vehicle* selectedVehicleGreen;

	GameObject* wall;
	GameObject *Menu;
	GameObject* background;

	// Vectors
	std::vector<Vehicle*> vehiclesGreen;
	std::vector<GameObject*> walls;
	std::vector<GameObject*> backgrounds;
	std::vector<GameObject*> players;

	std::vector<GLfloat> fullVertices =
	{
		// Position				// Color			// Texture Coords
		-0.5f,  0.5f, 0.0f,		0.0f, 1.0f,	1.0f,	0.0f, 0.0f,			// Top-Left
		 0.5f,  0.5f, 0.0f,		0.0f, 0.0f,	1.0f,	1.0f, 0.0f,			// Top-Right
		-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	0.0f, 1.0f,			// Bottom-Left
		 0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f,			// Bottom-Right
	};

	std::vector<GLfloat> slicedVertices =
	{
		// Position				// Color			// Texture Coords
		-0.5f,  0.5f, 0.0f,		0.0f, 1.0f,	1.0f,	0.0f, 0.001f,		// Top-Left
		 0.5f,  0.5f, 0.0f,		0.0f, 0.0f,	1.0f,	0.125f, 0.001f,		// Top-Right
		-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	0.0f, 0.2f,			// Bottom-Left
		 0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	0.125f, 0.2f,		// Bottom-Right
	};

	std::vector<GLfloat> slicedVertices2 =
	{
		// Position				// Color			// Texture Coords
		-0.5f,  0.5f, 0.0f,		0.0f, 1.0f,	1.0f,	0.0f, 0.2f,			// Top-Left
		 0.5f,  0.5f, 0.0f,		0.0f, 0.0f,	1.0f,	0.125f, 0.2f,		// Top-Right
		-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	0.0f, 0.4f,			// Bottom-Left
		 0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	0.125f, 0.4f,		// Bottom-Right
	};

	// Animation has 4 textures in one image
	std::vector<GLfloat> slicedVertices3 =
	{
		// Position				// Color			// Texture Coords
		-0.5f,  0.5f, 0.0f,		0.0f, 1.0f,	1.0f,	0.0f, 0.4f,			// Top-Left
		 0.5f,  0.5f, 0.0f,		0.0f, 0.0f,	1.0f,	0.125f, 0.4f,		// Top-Right
		-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	0.0f, 0.6f,			// Bottom-Left
		 0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	0.125f, 0.6f,		// Bottom-Right
	};

	std::vector<GLfloat> waterVertices =
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

	std::vector<GLuint> animationIndices =
	{
		1, 2, 3, // First Triangle
		1, 0, 2, // Second Triangle
	};
};

