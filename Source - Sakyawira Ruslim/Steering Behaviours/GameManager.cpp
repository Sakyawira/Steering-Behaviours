/***********************
  File Name   :   GameManager.cpp
  Description :   contains definition of GameManager class which control the creation, processing, and rendering of all objects
  Author      :   Sakyawira Nanda Ruslim
  Mail        :   Sakyawira@gmail.com
********************/
#include "GameManager.h"
#include <random>

/***********************
 Description :   Creates all the game objects
********************/
GameManager::GameManager()
{
	numberThreads = std::thread::hardware_concurrency();
	ThreadPool::GetInstance().Start(numberThreads);
	isInitialised = false;

	GameCamera = new Camera(windowWidth, windowHeight);

	// Create Clock
	clock = new Clock();
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
	steerText = new TextLabel(windowWidth, windowHeight, steerString, "Resources/Fonts/arial.ttf", glm::vec2(-350.0f, 350.0f));
	menuText = new TextLabel(windowWidth, windowHeight, m_string_menu, "Resources/Fonts/arial.ttf", glm::vec2(-169, 250.0f));
	instructionText = new TextLabel(windowWidth, windowHeight, m_string_instruction, "Resources/Fonts/arial.ttf", glm::vec2(-108, -250.0f));

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
	menu = new GameObject(alternatingShader, staticMesh, v_menu_texture, 0.0f, 0.0f);

	// Create Player
	Player = new GameObject(animateShader, playerMesh, v_texture2, 0.0f, 0.0f);
	players.push_back(Player);

	int border = 375 - static_cast<int>(Player->GetScale()) * 2;
	
	// Creating multiple slimes
	for (int i = 0; i < numberSlimes; ++i)
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

	// Creating walls around the playable space
	for (int j = -windowHeight; j <= windowHeight;)
	{
		for (int i = -windowWidth; i < windowWidth;)
		{
			wall = new GameObject(scrollingShader, waterMesh, v_water_texture, static_cast<float>(i), static_cast<float>(j));
			wall->Scale(50.0f);
			walls.push_back(wall);
			i += 50;
		}
		j += windowHeight * 2;
	}
	for (int j = -windowHeight; j <= windowHeight;)
	{
		for (int i = -windowWidth; i < windowWidth;)
		{
			wall = new GameObject(scrollingShader, waterMesh, v_water_texture, static_cast<float>(j), static_cast<float>(i));
			wall->Scale(50.0f);
			walls.push_back(wall);
			i += 50;
		}
		j += windowWidth * 2;
	}

	// Creates Background
	for (int j = -windowHeight; j <= windowHeight;)
	{
		for (int i = -windowWidth; i < windowWidth * 2;)
		{
			background = new GameObject(alternatingShader, staticMesh, bg_texture, static_cast<float>(i), static_cast<float>(j));
			background->Scale(800.0f);
			backgrounds.push_back(background);
			i += windowWidth;
		}
		j += windowHeight;
	}
	
	this->Initialize();
}

/***********************
 Description :   Deallocate memories from the game objects
********************/
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

	delete Player;
	Player = nullptr;
	//delete m_enemy_ice;

	delete menu;
	menu = nullptr;
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

	delete GameCamera;
	GameCamera = nullptr;

	ThreadPool::DestroyInstance();
}

/***********************
 Description :   Initialise values
********************/
void GameManager::Initialize()
{
	clock->Initialise();
	clock->Process();

	menuText->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	menuText->SetScale(0.5f);
	
	instructionText->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	instructionText->SetScale(0.39f);
	
	menu->Scale(800.0f);

	// Reset Player's variable
	Player->SetPosition(0.0f, 0.0f);
	Player->Scale(78.0f);

	// Reset Camera's Position
	GameCamera->SetPosX(0.0f);
	GameCamera->SetPosY(0.0f);

	ChangeBehaviourText();
	
	isInitialised = true;
	isEnded = false;
}

/***********************
 Description :   Loads main scene and activates loading screen
********************/
void GameManager::ProcessGame(Audio& audio, glm::vec3 mouse_location)
{
	if (isInitialised == 1)
	{
		float deltaTime = clock->GetDeltaTime() / 10.0f;

		if (isStarted)
		{
			if (Player->CurrentlyMoved)
			{
				// audio.Play(SOUND_CONSUME);
			}
			
			// Process Enemies using multi-threads
			for (int y = 0; y < numberSlimes - 1;)
			{
				int endY = y + static_cast<int>(numberSlimes / numberThreads);

				if (endY > numberSlimes)
				{
					endY = numberSlimes;
				}

				std::future<void>* newFuture = new std::future<void>;

				*newFuture = ThreadPool::GetInstance().Submit(processVehicles, &vehiclesGreen, y, endY, currentBehaviour, &vehiclesGreen, Player->GetPosition(), windowWidth, windowHeight, 0, deltaTime);

				futures.push_back(newFuture);
				y = endY;
			}

			for (auto& future : futures)
			{
				future->get();
				delete future;
				future = nullptr;
			}
			futures.clear();

			// Use single thread
			/*	for (auto& vehicle : vehiclesGreen) 
			{
				vehicle->Process(currentBehaviour, vehiclesGreen, player->GetLocation(), windowWidth, windowHeight, 0, deltaTime);
			}*/

			currentTime = static_cast<float>(glutGet(GLUT_ELAPSED_TIME)); // Get current time.
			currentTime = currentTime * 0.001f;
			steerText->SetText(steerString);
			steerText->SetPosition(glm::vec2(0 - (windowWidth / 2), (windowHeight / 2) - 50.0f) );
			steerText->SetScale(0.78f);
			steerText->SetColor(glm::vec3(0.91f, 0.13f, 0.13f));

			instructionString = "Press: (1) Seek, (2) Arrive, (3) Containment, (4) Wander, (5) Flock, (6) Leader Follow";
			instructionText->SetText(instructionString);
			instructionText->SetPosition(glm::vec2(-351.0f, 50 - (windowHeight/2)));
			instructionText->SetColor(glm::vec3(0.26f, 0.0f, 0.26f));

			menuString = "Press: (W), (A), (S), (D) to move the player.";
			menuText->SetText(menuString);
			menuText->SetPosition(glm::vec2(-221, -390.0f));
			menuText->SetColor(glm::vec3(0.78f, 0.0f, 0.26f));
		}

		clock->Process();
		Player->CurrentlyMoved = false;
	}
	else
	{
		this->Initialize();
	}
}

/***********************
 Description :   Checks player collision with walls
********************/
bool GameManager::CollisionCheck(float _top, float _bottom, float _left, float _right)
{
	// Check whether or not the position is occupied by an obstacle
	for (auto& gameObjects : players)
	{
		for (auto& gameObjects2 : walls)
		{
			// Check ahead if the game object will get stuck if continue moving in a certain direction
			if (gameObjects->GetBoundingCoordinate(CoordinateID::RIGHT) + _right >= gameObjects2->GetBoundingCoordinate(CoordinateID::LEFT)
				&& gameObjects->GetBoundingCoordinate(CoordinateID::LEFT) - _left <= gameObjects2->GetBoundingCoordinate(CoordinateID::RIGHT)
				&& gameObjects->GetBoundingCoordinate(CoordinateID::BOTTOM) - _bottom <= gameObjects2->GetBoundingCoordinate(CoordinateID::TOP)
				&& gameObjects->GetBoundingCoordinate(CoordinateID::TOP) + _top >= gameObjects2->GetBoundingCoordinate(CoordinateID::BOTTOM))
			{
				// Push the game object out if it is stuck inside a collision box
				while (gameObjects->GetBoundingCoordinate(CoordinateID::RIGHT) >= gameObjects2->GetBoundingCoordinate(CoordinateID::LEFT)
					&& gameObjects->GetBoundingCoordinate(CoordinateID::LEFT) <= gameObjects2->GetBoundingCoordinate(CoordinateID::RIGHT)
					&& gameObjects->GetBoundingCoordinate(CoordinateID::BOTTOM) <= gameObjects2->GetBoundingCoordinate(CoordinateID::TOP)
					&& gameObjects->GetBoundingCoordinate(CoordinateID::TOP) >= gameObjects2->GetBoundingCoordinate(CoordinateID::BOTTOM))
				{
					if (_top > 0)
					{
						gameObjects->Move(MoveDirection::MOVE_DOWN, PlayerSize + 1);
						GameCamera->MovePosY(-2.0f);
					}
					else if (_bottom > 0)
					{
						gameObjects->Move(MoveDirection::MOVE_UP, PlayerSize + 1);
						GameCamera->MovePosY(2.0f);
					}
					else if (_left > 0)
					{
						gameObjects->Move(MoveDirection::MOVE_RIGHT, PlayerSize + 1);
						GameCamera->MovePosX(2.0f);
					}
					else if (_right > 0)
					{
						gameObjects->Move(MoveDirection::MOVE_LEFT, PlayerSize + 1);
						GameCamera->MovePosX(-2.0f);
					}
				}
				return true;
			}
		}
	}
	return false;
}

/***********************
 Description :   Render game objects
********************/
void GameManager::Render()
{
	if (isInitialised == 1)
	{
		// Drawing background
		for (auto& backgroundObjects : backgrounds)
		{
			backgroundObjects->Draw(*GameCamera, "currentTime", currentTime);
		}

		// Drawing all players
		for (auto& playerObjects : players)
		{
			playerObjects->Draw(*GameCamera, "currentTime", currentTime, "frameCounts", static_cast<int>(frameCounts));
		}
		
		// Drawing all obstacles
		for (auto& coinObjects : vehiclesGreen)
		{
			coinObjects->Draw(*GameCamera, "currentTime", currentTime, "frameCounts", static_cast<int>(frameCounts));
		}

		// Draw all collectables
		for (auto& obstacleObjects : walls)
		{
			obstacleObjects->Draw(*GameCamera, "currentTime", currentTime);
		}

		//m_enemy_ice->Draw(camera, "currentTime", currentTime, "frameCounts", static_cast<int>(frameCounts));

		if (Player->GetScale() <= 0.13f || isStarted == 0)
		{
			menu->Draw(*GameCamera, "currentTime", currentTime);
			Player->Draw(*GameCamera, "currentTime", currentTime, "frameCounts", static_cast<int>(frameCounts));
		}
		
		if (steerText != nullptr)
		{
			steerText->Render();
		}

		// Render instruction
		instructionText->Render();
		menuText->Render();
		
		frameCounts += 1.0f * clock->GetDeltaTime() / 10.0f;
	}
	else
	{
		this->Initialize();
	}
}

/***********************
 Description :   Check if the game has started
********************/
bool GameManager::IsStarted()
{
	return isStarted;
}

/***********************
 Description :   Check if the game has ended
********************/
bool GameManager::IsEnded()
{
	return isEnded;
}

/***********************
 Description :   Start the game
********************/
void GameManager::StartGame()
{
	isStarted = true;
}

/***********************
 Description :   Change the behaviour of the vehicles
********************/
void GameManager::SetBehaviour(Behaviour steer)
{
	currentBehaviour = steer;
}

/***********************
 Description :   Loads main scene and activates loading screen
********************/
void GameManager::ChangeBehaviourText()
{
	switch (currentBehaviour) {
	case Behaviour::SEEK:
		steerString = "Seek";
		break;
	case Behaviour::ARRIVE:
		steerString = "Arrive";
		break;
	case Behaviour::CONTAINMENT:
		steerString = "Wander";
		break;
	case Behaviour::WANDER:
		steerString = "Containment";
		break;
	case Behaviour::FLOCK:
		steerString = "Flock";
		break;
	case Behaviour::LEAD_FOLLOWING:
		steerString = "Leader Following";
		break;
	}
}

/***********************
 Description :   A callback function to be assign to a thread
********************/
void GameManager::processVehicles(std::vector<Vehicle*>* _vehicles, int y, int endY, Behaviour _steer, std::vector<Vehicle*>* _boids, glm::vec3 _targetLocation, int _windowWidth, int _windowHeight, int _playerSize, float _deltaTime)
{
	for (int i = y; i < endY; i++)
	{
		// std::cout << "Thread number " << std::this_thread::get_id() << " executing vehicle number " << i << std::endl;
		std::vector<Vehicle*>& veh = *_vehicles;
		(veh[i])->Process(_steer, *_boids, _targetLocation, _windowWidth, _windowHeight, _playerSize, _deltaTime);
	}
}

/***********************
 Description :   Gets the clock
********************/
Clock * GameManager::GetClock()
{
	return clock;
}