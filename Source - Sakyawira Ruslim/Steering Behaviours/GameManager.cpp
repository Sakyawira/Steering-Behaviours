/***********************
  Bachelor of Software Engineering
  Media Design School
  Auckland
  New Zealand

  (c) 2018 Media Design School

  File Name   :   GameObject.h
  Description :   contains definition of GameManager class which control the gameplay, rendering of all game objects
  Author      :   Sakyawira Nanda Ruslim
  Mail        :   Sakyawira.Rus8080@mediadesign.school.nz
********************/
#include "GameManager.h"
#include <random>

GameManager::GameManager()
{
	isInitialised = false;

	// Create Clock
	clock = new CClock();
	// Create Shader
	alternatingShader = new Shader("Resources/Shaders/AlternatingVertex.txt", "Resources/Shaders/AlternatingFragment.txt");
	animateShader = new Shader("Resources/Shaders/AnimationVertex.txt", "Resources/Shaders/AnimationFragment.txt");
	scrollingShader = new Shader("Resources/Shaders/ScrollingVertex.txt", "Resources/Shaders/AnimationFragment.txt");

	// Create Mesh
	staticMesh = new Mesh(animationIndices, fullVertices);
	vehicleGreenMesh = new Mesh(animationIndices, slicedVertices3);
	vehicleBlueMesh = new Mesh(animationIndices, slicedVertices2);
	waterMesh = new Mesh(animationIndices, slicedVertices3);
	playerMesh = new Mesh(animationIndices, slicedVertices);

	// Text
	std::string m_string_menu = "Sakyawira's Steering Behaviours";
	std::string m_string_instruction = "Press 'R' to start the game...";
	steerText = new TextLabel(WINDOW_WIDHT, WINDOW_HEIGHT, steerString, "Resources/Fonts/arial.ttf", glm::vec2(-350.0f, 350.0f));
	menuText = new TextLabel(WINDOW_WIDHT, WINDOW_HEIGHT, m_string_menu, "Resources/Fonts/arial.ttf", glm::vec2(-169, 250.0f));
	instructionText = new TextLabel(WINDOW_WIDHT, WINDOW_HEIGHT, m_string_instruction, "Resources/Fonts/arial.ttf", glm::vec2(-108, -250.0f));

	// Texture
	starsTexture = new Texture("Resources/Textures/stars.png");
	backgroundTexture = new Texture("Resources/Textures/bg.png");
	slimesTexture = new Texture("Resources/Textures/Slimes.png");
	waterTexture = new Texture("Resources/Textures/water.png");
	menuTexture = new Texture("Resources/Textures/Menu.png");

	// Texture Vectors to be passed in
	std::vector<Texture*> v_water_texture = { waterTexture, waterTexture };
	std::vector<Texture*> v_menu_texture = { menuTexture, menuTexture };
	std::vector<Texture*> v_texture2 = { slimesTexture, slimesTexture };
	std::vector<Texture*> v_texture = { starsTexture, backgroundTexture };
	std::vector<Texture*> bg_texture = { backgroundTexture, backgroundTexture };

	// Create Menu Object
	Menu = new GameObject(alternatingShader, staticMesh, v_menu_texture, 0.0f, 0.0f);

	// Create Player
	player = new GameObject(animateShader, playerMesh, v_texture2, 0.0f, 0.0f);
	players.push_back(player);

	int border = 375 - static_cast<int>(player->GetScale()) * 2;
	
	// Creating multiple coins
	for (int i = 0; i < 50; ++i)
	{
		int negate = rand() % 2;
		negate = (negate == 0 ? -1 : 1);
		const float random_x = static_cast<float>((rand() % border) * negate);
		negate = rand() % 2;
		negate = (negate == 0 ? -1 : 1);

		const float random_y = static_cast<float>((rand() % border) * negate);
		selectedVehicleGreen = new Vehicle(animateShader, vehicleGreenMesh, v_texture2, random_x, random_y);
		selectedVehicleGreen->Scale(50.0f);
		vehiclesGreen.push_back(selectedVehicleGreen);
	}

	// Creates enemy
	for (int i = 0; i < 1; ++i)
	{
		int negate = rand() % 2;
		negate = (negate == 0 ? -1 : 1);
		const float random_x = static_cast<float>((rand() % border) * negate);
		negate = rand() % 2;
		negate = (negate == 0 ? -1 : 1);
		const float random_y = static_cast<float>((rand() % border) * negate);
	}

	// Creating walls around the playable space
	for (int j = -WINDOW_HEIGHT; j <= WINDOW_HEIGHT;)
	{
		for (int i = -WINDOW_WIDHT; i < WINDOW_WIDHT;)
		{
			wall = new GameObject(scrollingShader, waterMesh, v_water_texture, static_cast<float>(i), static_cast<float>(j));
			wall->Scale(50.0f);
			walls.push_back(wall);
			i += 50;
		}
		j += WINDOW_HEIGHT * 2;
	}
	for (int j = -WINDOW_HEIGHT; j <= WINDOW_HEIGHT;)
	{
		for (int i = -WINDOW_WIDHT; i < WINDOW_WIDHT;)
		{
			wall = new GameObject(scrollingShader, waterMesh, v_water_texture, static_cast<float>(j), static_cast<float>(i));
			wall->Scale(50.0f);
			walls.push_back(wall);
			i += 50;
		}
		j += WINDOW_WIDHT * 2;
	}

	// Creates Background
	for (int j = -WINDOW_HEIGHT; j <= WINDOW_HEIGHT;)
	{
		for (int i = -WINDOW_WIDHT; i < WINDOW_WIDHT * 2;)
		{
			background = new GameObject(alternatingShader, staticMesh, bg_texture, static_cast<float>(i), static_cast<float>(j));
			background->Scale(800.0f);
			backgrounds.push_back(background);
			i += WINDOW_WIDHT;
		}
		j += WINDOW_HEIGHT;
	}
	
	this->Initialize();
}

GameManager::~GameManager()
{
	delete instructionText;
	instructionText = nullptr;
	
	delete menuText;
	menuText = nullptr;
	
	delete staticMesh;
	staticMesh = nullptr;
	delete vehicleGreenMesh;
	vehicleGreenMesh = nullptr;
	delete vehicleBlueMesh;
	vehicleBlueMesh = nullptr;
	delete waterMesh;
	waterMesh = nullptr;
	delete playerMesh;
	playerMesh = nullptr;

	delete alternatingShader;
	alternatingShader = nullptr;
	delete animateShader;
	animateShader = nullptr;
	delete scrollingShader;
	scrollingShader = nullptr;

	delete starsTexture;
	starsTexture = nullptr;
	delete backgroundTexture;
	backgroundTexture = nullptr;
	delete slimesTexture;
	slimesTexture = nullptr;
	delete waterTexture;
	waterTexture = nullptr;

	delete steerText;
	steerText = nullptr;

	delete player;
	player = nullptr;
	//delete m_enemy_ice;

	delete Menu;
	Menu = nullptr;
	delete menuTexture;
	menuTexture = nullptr;

	for (auto& backgroundObjects : backgrounds)
	{
		delete backgroundObjects;
		backgroundObjects = nullptr;
	}

	for (auto& coinObjects : vehiclesGreen)
	{
		delete coinObjects;
		coinObjects = nullptr;
	}
	for (auto& obstacleObjects : walls)
	{
		delete obstacleObjects;
		obstacleObjects = nullptr;
	}
	delete clock;
	clock = nullptr;
}

void GameManager::Initialize()
{
	clock->Initialise();
	clock->Process();

	menuText->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	menuText->SetScale(0.5f);
	
	instructionText->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	instructionText->SetScale(0.39f);
	
	Menu->Scale(800.0f);

	// Reset Player's variable
	player->SetPosition(0.0f, 0.0f);
	player->Scale(78.0f);

	// Reset Camera's Position
	camera.SetPosX(0.0f);
	camera.SetPosY(0.0f);

	// Reset score
	// m_i_steer = 0;
	ChangeBehaviourText();
	
	isInitialised = true;
	isEnded = false;
}

void GameManager::ProcessGame(Audio& audio, glm::vec3 mouse_location)
{
	if (isInitialised == 1)
	{
		float deltaTime = clock->GetDeltaTick() * 120.0f;

		if (isStarted)
		{
			if (player->currentlyMoved)
			{
				// audio.Play(SOUND_CONSUME);
			}
			
			// Process Enemies
			for (auto& vehicle : vehiclesGreen)
			{
				vehicle->Process(currentBehaviour, vehiclesGreen, player->GetLocation(), WINDOW_WIDHT, WINDOW_HEIGHT, 0, deltaTime);
			}

			currentTime = static_cast<float>(glutGet(GLUT_ELAPSED_TIME)); // Get current time.
			currentTime = currentTime * 0.001f;
			steerText->SetText(steerString);
			steerText->SetPosition(glm::vec2(-390.0f, 350.0f));
			steerText->SetScale(0.78f);
			steerText->SetColor(glm::vec3(0.91f, 0.13f, 0.13f));

			instructionString = "Press: (1) Seek, (2) Arrive, (3) Containment, (4) Wander, (5) Flock, (6) Leader Follow";
			instructionText->SetText(instructionString);
			instructionText->SetPosition(glm::vec2(-351.0f, -365.0f));
			instructionText->SetColor(glm::vec3(0.26f, 0.0f, 0.26f));

			menuString = "Press: (W), (A), (S), (D) to move the player.";
			menuText->SetText(menuString);
			menuText->SetPosition(glm::vec2(-221, -390.0f));
			menuText->SetColor(glm::vec3(0.78f, 0.0f, 0.26f));
		}

		clock->Process();
		player->currentlyMoved = false;
	}
	else
	{
		this->Initialize();
	}
}

bool GameManager::CollisionCheck(float _top, float _bottom, float _left, float _right)
{
	// Check whether or not the position is occupied by an obstacle
	for (auto& gameObjects : players)
	{
		for (auto& gameObjects2 : walls)
		{
			// Check ahead if the game object will get stuck if continue moving in a certain direction
			if (gameObjects->GetPosition(RIGHT) + _right >= gameObjects2->GetPosition(LEFT)
				&& gameObjects->GetPosition(LEFT) - _left <= gameObjects2->GetPosition(RIGHT)
				&& gameObjects->GetPosition(BOTTOM) - _bottom <= gameObjects2->GetPosition(TOP)
				&& gameObjects->GetPosition(TOP) + _top >= gameObjects2->GetPosition(BOTTOM))
			{
				// Push the game object out if it is stuck inside a collision box
				while (gameObjects->GetPosition(RIGHT) >= gameObjects2->GetPosition(LEFT)
					&& gameObjects->GetPosition(LEFT) <= gameObjects2->GetPosition(RIGHT)
					&& gameObjects->GetPosition(BOTTOM) <= gameObjects2->GetPosition(TOP)
					&& gameObjects->GetPosition(TOP) >= gameObjects2->GetPosition(BOTTOM))
				{
					if (_top > 0)
					{
						gameObjects->Move(MOVE_DOWN, playerSize + 1);
						camera.MovePosY(-2.0f);
					}
					else if (_bottom > 0)
					{
						gameObjects->Move(MOVE_UP, playerSize + 1);
						camera.MovePosY(2.0f);
					}
					else if (_left > 0)
					{
						gameObjects->Move(MOVE_RIGHT, playerSize + 1);
						camera.MovePosX(2.0f);
					}
					else if (_right > 0)
					{
						gameObjects->Move(MOVE_LEFT, playerSize + 1);
						camera.MovePosX(-2.0f);
					}
				}
				return true;
			}
		}
	}
	
	return false;
}

void GameManager::Render()
{
	if (isInitialised == 1)
	{
		// Drawing background
		for (auto& backgroundObjects : backgrounds)
		{
			backgroundObjects->Draw(camera, "currentTime", currentTime);
		}

		// Drawing all players
		for (auto& playerObjects : players)
		{
			playerObjects->Draw(camera, "currentTime", currentTime, "frameCounts", static_cast<int>(frameCounts));
		}
		
		// Drawing all obstacles
		for (auto& coinObjects : vehiclesGreen)
		{
			coinObjects->Draw(camera, "currentTime", currentTime, "frameCounts", static_cast<int>(frameCounts));
		}

		// Draw all collectables
		for (auto& obstacleObjects : walls)
		{
			obstacleObjects->Draw(camera, "currentTime", currentTime);
		}

		//m_enemy_ice->Draw(camera, "currentTime", currentTime, "frameCounts", static_cast<int>(frameCounts));

		if (player->GetScale() <= 0.13f || isStarted == 0)
		{
			Menu->Draw(camera, "currentTime", currentTime);
			player->Draw(camera, "currentTime", currentTime, "frameCounts", static_cast<int>(frameCounts));
		}
		
		if (steerText != nullptr)
		{
			steerText->Render();
		}

		// Render instruction
		instructionText->Render();
		menuText->Render();
		
		frameCounts += 1.0f * clock->GetDeltaTick() * 120.0f;
	}
	else
	{
		this->Initialize();
	}
}

bool GameManager::IsStarted()
{
	return isStarted;
}

bool GameManager::IsEnded()
{
	return isEnded;
}

void GameManager::StartGame()
{
	isStarted = true;
}

void GameManager::SetBehaviour(Behaviour steer)
{
	currentBehaviour = steer;
}

void GameManager::ChangeBehaviourText()
{
	if (currentBehaviour == SEEK)
	{
		steerString = "Seek";
	}

	else if (currentBehaviour == ARRIVE)
	{
		steerString = "Arrive";
	}

	else if (currentBehaviour == WANDER)
	{
		steerString = "Wander";
	}

	else if (currentBehaviour == CONTAINMENT)
	{
		steerString = "Containment";
	}

	else if (currentBehaviour == FLOCK)
	{
		steerString = "Flock";
	}
	else if (currentBehaviour == LEAD_FOLLOWING)
	{
		steerString = "Leader Following";
	}
}

CClock * GameManager::GetClock()
{
	return clock;
}
