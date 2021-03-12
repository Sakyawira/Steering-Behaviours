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
	staticMesh = new Mesh(animation_indices, static_vertices);
	vehicleGreenMesh = new Mesh(animation_indices, animation_vertices);
	vehicleBlueMesh = new Mesh(animation_indices, enemy2_vertices);
	waterMesh = new Mesh(animation_indices, animation_vertices);
	playerMesh = new Mesh(animation_indices, player_animation_vertices);

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

	srand(static_cast<unsigned>(std::random_device()()));
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
		selectedVehicleBlue = new Vehicle(animateShader, vehicleBlueMesh, v_texture2, random_x, random_y);
		selectedVehicleBlue->Scale(75.0f);
		selectedVehicleBlue->RandomOn();
		vehiclesBlue.push_back(selectedVehicleBlue);
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
	for (auto& coinObjects2 : vehiclesBlue)
	{
		delete coinObjects2;
		coinObjects2 = nullptr;
	}
	for (auto& obstacleObjects : walls)
	{
		delete obstacleObjects;
		obstacleObjects = nullptr;
	}
	for (auto& erasedObjects : vehiclesGreenRemoved)
	{
		delete erasedObjects;
		erasedObjects = nullptr;
	}
	for (auto& erasedObjects2 : vehiclesBlueRemoved)
	{
		delete erasedObjects2;
		erasedObjects2 = nullptr;
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

	// Re-enable All Enemies
	while (!vehiclesGreenRemoved.empty())
	{
		vehiclesGreen.push_back(vehiclesGreenRemoved.back());
		vehiclesGreenRemoved.pop_back();
		vehiclesGreen.back()->Enable();
	}
	while (!vehiclesBlueRemoved.empty())
	{
		vehiclesBlue.push_back(vehiclesBlueRemoved.back());
		vehiclesBlueRemoved.pop_back();
		vehiclesBlue.back()->Enable();
	}
	
	isInitialised = true;
	isEnded = false;
}

void GameManager::ProcessGame(Audio& audio, glm::vec3 mouse_location)
{
	// steer  
	if (isInitialised == 1)
	{
		float f_deltaT = clock->GetDeltaTick() * 120.0f;

		if (isStarted)
		{
			if (player->currentlyMoved)
			{
				// audio.Play(SOUND_CONSUME);
			}
			
			// Process Enemies
			for (auto& coinObjects : vehiclesGreen)
			{
				coinObjects->process(currentBehaviour, vehiclesGreen, player->GetLocation(), WINDOW_WIDHT, WINDOW_HEIGHT, 0, f_deltaT);
			}
			for (auto& coinObjects2 : vehiclesBlue)
			{
				coinObjects2->process(currentBehaviour, vehiclesGreen, player->GetLocation(), WINDOW_WIDHT, WINDOW_HEIGHT, 0, f_deltaT);
			}
			// Check if collide with enemy every frame

			// Re-spawn Enemies
			if (vehiclesGreen.empty())
			{
				while (!vehiclesGreenRemoved.empty())
				{
					vehiclesGreen.push_back(vehiclesGreenRemoved.back());
					vehiclesGreenRemoved.pop_back();
					vehiclesGreen.back()->Enable();
				}
				int i = vehiclesGreenRemoved.size();
			}
			if (vehiclesBlue.empty())
			{
				while (!vehiclesBlueRemoved.empty())
				{
					vehiclesBlue.push_back(vehiclesBlueRemoved.back());
					vehiclesBlueRemoved.pop_back();
					vehiclesBlue.back()->Enable();
				}
				int i = vehiclesBlueRemoved.size();
			}
			currentTime = static_cast<float>(glutGet(GLUT_ELAPSED_TIME)); // Get current time.
			currentTime = currentTime * 0.001f;
			steerText->SetText(steerString);
			steerText->SetPosition(glm::vec2(-390.0f, 350.0f));
			steerText->SetScale(0.78f);
			steerText->SetColor(glm::vec3(0.91f, 0.13f, 0.13f));

			if (player->GetScale() <= 0.13f)
			{
				menuString = "You're Burnt Out!";
				instructionString = "Press 'R' to play again...";
				menuText->SetText(menuString);
				instructionText->SetText(instructionString);
				camera.SetPosX(0.0f);
				camera.SetPosY(0.0f);
				isEnded = true;
			}
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

void GameManager::EnemyCollisionCheck()
{
	// Check whether or not a position is occupied by a m_enemy_earth
	std::vector<Vehicle*>::iterator it_vec_game_object;
	for (auto& gameObjects : players)
	{
		for (auto& gameObjects2 : vehiclesGreen)
		{
			if (gameObjects->GetPosition(RIGHT) >= gameObjects2->GetPosition(LEFT)
				&& gameObjects->GetPosition(LEFT) <= gameObjects2->GetPosition(RIGHT)
				&& gameObjects->GetPosition(BOTTOM) <= gameObjects2->GetPosition(TOP)
				&& gameObjects->GetPosition(TOP) >= gameObjects2->GetPosition(BOTTOM))
			{
				std::cout << "m_enemy_earth found!" << std::endl;
				gameObjects2->Disable();
				vehiclesGreenRemoved.push_back(gameObjects2);
				// if you remove it from the vector, it will not be deleted
				// but if you don't, it will still be checked every frame, and you will still collide with it
				it_vec_game_object = std::remove(vehiclesGreen.begin(), vehiclesGreen.end(), gameObjects2);
				// There I push it to another vector to keep it's address, so I can delete it at the end of the game
				vehiclesGreen.erase(it_vec_game_object);
			}
		}
	}
}

void GameManager::EnemyCollisionCheck2()
{
	// Check whether or not a position is occupied by a m_enemy_earth
	std::vector<Vehicle*>::iterator it_vec_game_object;
	for (auto& gameObjects : players)
	{
		for (auto& gameObjects2 : vehiclesBlue)
		{
			if (gameObjects->GetPosition(RIGHT) >= gameObjects2->GetPosition(LEFT)
				&& gameObjects->GetPosition(LEFT) <= gameObjects2->GetPosition(RIGHT)
				&& gameObjects->GetPosition(BOTTOM) <= gameObjects2->GetPosition(TOP)
				&& gameObjects->GetPosition(TOP) >= gameObjects2->GetPosition(BOTTOM))
			{
				std::cout << "m_enemy_earth found!" << std::endl;
				gameObjects2->Disable();
				vehiclesBlueRemoved.push_back(gameObjects2);
				// if you remove it from the vector, it will not be deleted
				// but if you don't, it will still be checked every frame, and you will still collide with it
				it_vec_game_object = std::remove(vehiclesBlue.begin(), vehiclesBlue.end(), gameObjects2);
				// There I push it to another vector to keep it's address, so I can delete it at the end of the game
				vehiclesBlue.erase(it_vec_game_object);
			}
		}
	}
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
		for (auto& coinObjects2 : vehiclesBlue)
		{
			coinObjects2->Draw(camera, "currentTime", currentTime, "frameCounts", static_cast<int>(frameCounts));
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
