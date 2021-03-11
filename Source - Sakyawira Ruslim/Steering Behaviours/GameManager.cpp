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
	m_b_initialized = false;

	// Create Clock
	m_clock = new CClock();
	// Create Shader
	m_sh_alternating = new Shader("Resources/Shaders/AlternatingVertex.txt", "Resources/Shaders/AlternatingFragment.txt");
	m_sh_animate = new Shader("Resources/Shaders/AnimationVertex.txt", "Resources/Shaders/AnimationFragment.txt");
	m_sh_scroll = new Shader("Resources/Shaders/ScrollingVertex.txt", "Resources/Shaders/AnimationFragment.txt");

	// Create Mesh
	m_mesh_static = new Mesh(animation_indices, static_vertices);
	m_mesh_animate = new Mesh(animation_indices, animation_vertices);
	m_mesh_animate2 = new Mesh(animation_indices, enemy2_vertices);
	m_mesh_scroll = new Mesh(animation_indices, animation_vertices);
	m_mesh_player = new Mesh(animation_indices, player_animation_vertices);

	// Text
	std::string m_string_menu = "Sakyawira's Steering Behaviours";
	std::string m_string_instruction = "Press 'R' to start the game...";
	m_text_steer = new TextLabel(WINDOW_WIDHT, WINDOW_HEIGHT, m_string_steer, "Resources/Fonts/arial.ttf", glm::vec2(-350.0f, 350.0f));
	m_text_menu = new TextLabel(WINDOW_WIDHT, WINDOW_HEIGHT, m_string_menu, "Resources/Fonts/arial.ttf", glm::vec2(-169, 250.0f));
	m_text_instruction = new TextLabel(WINDOW_WIDHT, WINDOW_HEIGHT, m_string_instruction, "Resources/Fonts/arial.ttf", glm::vec2(-108, -250.0f));

	// Texture
	m_tr_stars = new Texture("Resources/Textures/stars.png");
	m_tr_background = new Texture("Resources/Textures/bg.png");
	m_tr_slimes = new Texture("Resources/Textures/Slimes.png");
	m_tr_water = new Texture("Resources/Textures/water.png");
	m_tr_menu = new Texture("Resources/Textures/Menu.png");

	// Texture Vectors to be passed in
	std::vector<Texture*> v_water_texture = { m_tr_water, m_tr_water };
	std::vector<Texture*> v_menu_texture = { m_tr_menu, m_tr_menu };
	std::vector<Texture*> v_texture2 = { m_tr_slimes, m_tr_slimes };
	std::vector<Texture*> v_texture = { m_tr_stars, m_tr_background };
	std::vector<Texture*> bg_texture = { m_tr_background, m_tr_background };

	// Create Menu Object
	Menu = new GameObject(m_sh_alternating, m_mesh_static, v_menu_texture, 0.0f, 0.0f);

	// Create Player
	player = new GameObject(m_sh_animate, m_mesh_player, v_texture2, 0.0f, 0.0f);
	m_vector_playerObjects.push_back(player);

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
		m_enemy_earth = new Vehicle(m_sh_animate, m_mesh_animate, v_texture2, random_x, random_y);
		m_enemy_earth->Scale(50.0f);
		m_vector_enemyEarth.push_back(m_enemy_earth);
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
		m_enemy_ice = new Vehicle(m_sh_animate, m_mesh_animate2, v_texture2, random_x, random_y);
		m_enemy_ice->Scale(75.0f);
		m_enemy_ice->RandomOn();
		m_vector_enemyIce.push_back(m_enemy_ice);
	}

	// Creating walls around the playable space
	for (int j = -WINDOW_HEIGHT; j <= WINDOW_HEIGHT;)
	{
		for (int i = -WINDOW_WIDHT; i < WINDOW_WIDHT;)
		{
			wall = new GameObject(m_sh_scroll, m_mesh_scroll, v_water_texture, static_cast<float>(i), static_cast<float>(j));
			wall->Scale(50.0f);
			m_vector_obstacleObjects.push_back(wall);
			i += 50;
		}
		j += WINDOW_HEIGHT * 2;
	}
	for (int j = -WINDOW_HEIGHT; j <= WINDOW_HEIGHT;)
	{
		for (int i = -WINDOW_WIDHT; i < WINDOW_WIDHT;)
		{
			wall = new GameObject(m_sh_scroll, m_mesh_scroll, v_water_texture, static_cast<float>(j), static_cast<float>(i));
			wall->Scale(50.0f);
			m_vector_obstacleObjects.push_back(wall);
			i += 50;
		}
		j += WINDOW_WIDHT * 2;
	}

	// Creates Background
	for (int j = -WINDOW_HEIGHT; j <= WINDOW_HEIGHT;)
	{
		for (int i = -WINDOW_WIDHT; i < WINDOW_WIDHT * 2;)
		{
			background = new GameObject(m_sh_alternating, m_mesh_static, bg_texture, static_cast<float>(i), static_cast<float>(j));
			background->Scale(800.0f);
			m_vector_backgroundObjects.push_back(background);
			i += WINDOW_WIDHT;
		}
		j += WINDOW_HEIGHT;
	}
	
	this->Initialize();
}

GameManager::~GameManager()
{
	delete m_text_instruction;
	m_text_instruction = nullptr;
	
	delete m_text_menu;
	m_text_menu = nullptr;
	
	delete m_mesh_static;
	m_mesh_static = nullptr;
	delete m_mesh_animate;
	m_mesh_animate = nullptr;
	delete m_mesh_animate2;
	m_mesh_animate2 = nullptr;
	delete m_mesh_scroll;
	m_mesh_scroll = nullptr;
	delete m_mesh_player;
	m_mesh_player = nullptr;

	delete m_sh_alternating;
	m_sh_alternating = nullptr;
	delete m_sh_animate;
	m_sh_animate = nullptr;
	delete m_sh_scroll;
	m_sh_scroll = nullptr;

	delete m_tr_stars;
	m_tr_stars = nullptr;
	delete m_tr_background;
	m_tr_background = nullptr;
	delete m_tr_slimes;
	m_tr_slimes = nullptr;
	delete m_tr_water;
	m_tr_water = nullptr;

	delete m_text_steer;
	m_text_steer = nullptr;

	delete player;
	player = nullptr;
	//delete m_enemy_ice;

	delete Menu;
	Menu = nullptr;
	delete m_tr_menu;
	m_tr_menu = nullptr;

	for (auto& backgroundObjects : m_vector_backgroundObjects)
	{
		delete backgroundObjects;
		backgroundObjects = nullptr;
	}

	for (auto& coinObjects : m_vector_enemyEarth)
	{
		delete coinObjects;
		coinObjects = nullptr;
	}
	for (auto& coinObjects2 : m_vector_enemyIce)
	{
		delete coinObjects2;
		coinObjects2 = nullptr;
	}
	for (auto& obstacleObjects : m_vector_obstacleObjects)
	{
		delete obstacleObjects;
		obstacleObjects = nullptr;
	}
	for (auto& erasedObjects : m_vector_erasedEarth)
	{
		delete erasedObjects;
		erasedObjects = nullptr;
	}
	for (auto& erasedObjects2 : m_vector_erasedIce)
	{
		delete erasedObjects2;
		erasedObjects2 = nullptr;
	}
	delete m_clock;
	m_clock = nullptr;
}

void GameManager::Initialize()
{
	m_clock->Initialise();
	m_clock->Process();

	m_text_menu->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	m_text_menu->SetScale(0.5f);
	
	m_text_instruction->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	m_text_instruction->SetScale(0.39f);
	
	Menu->Scale(800.0f);

	// Reset Player's variable
	player->SetPosition(0.0f, 0.0f);
	player->Scale(78.0f);

	// Reset Camera's Position
	camera.SetPosX(0.0f);
	camera.SetPosY(0.0f);

	// Reset score
	// m_i_steer = 0;
	change_behaviour_text();

	// Re-enable All Enemies
	while (!m_vector_erasedEarth.empty())
	{
		m_vector_enemyEarth.push_back(m_vector_erasedEarth.back());
		m_vector_erasedEarth.pop_back();
		m_vector_enemyEarth.back()->Enable();
	}
	while (!m_vector_erasedIce.empty())
	{
		m_vector_enemyIce.push_back(m_vector_erasedIce.back());
		m_vector_erasedIce.pop_back();
		m_vector_enemyIce.back()->Enable();
	}
	
	m_b_initialized = true;
	m_b_ended = false;
}

void GameManager::ProcessGame(Audio& audio, glm::vec3 mouse_location)
{
	// steer  
	if (m_b_initialized == 1)
	{
		float f_deltaT = m_clock->GetDeltaTick() * 120.0f;

		if (m_b_start)
		{
			if (player->m_currently_moved)
			{
				// audio.Play(SOUND_CONSUME);
			}
			
			// Process Enemies
			for (auto& coinObjects : m_vector_enemyEarth)
			{
				coinObjects->process(m_steering, m_vector_enemyEarth, player->GetLocation(), WINDOW_WIDHT, WINDOW_HEIGHT, 0, f_deltaT);
			}
			for (auto& coinObjects2 : m_vector_enemyIce)
			{
				coinObjects2->process(m_steering, m_vector_enemyEarth, player->GetLocation(), WINDOW_WIDHT, WINDOW_HEIGHT, 0, f_deltaT);
			}
			// Check if collide with enemy every frame
			//	Enemy_Collision_Check();
			//	Enemy_Collision_Check2();

			// Re-spawn Enemies
			if (m_vector_enemyEarth.empty())
			{
				while (!m_vector_erasedEarth.empty())
				{
					m_vector_enemyEarth.push_back(m_vector_erasedEarth.back());
					m_vector_erasedEarth.pop_back();
					m_vector_enemyEarth.back()->Enable();
				}
				int i = m_vector_erasedEarth.size();
			}
			if (m_vector_enemyIce.empty())
			{
				while (!m_vector_erasedIce.empty())
				{
					m_vector_enemyIce.push_back(m_vector_erasedIce.back());
					m_vector_erasedIce.pop_back();
					m_vector_enemyIce.back()->Enable();
				}
				int i = m_vector_erasedIce.size();
			}

			//// Process player
			//if (player->GetScale() >= 0.13f)
			//{
			//	player->Scale(player->GetScale() - 0.039f * f_deltaT);
			//}

			currentTime = static_cast<float>(glutGet(GLUT_ELAPSED_TIME)); // Get current time.
			currentTime = currentTime * 0.001f;

			// Update Texts
			/*m_string_steer = "Behaviour type = " + std::to_string(m_i_steer);*/
			m_text_steer->SetText(m_string_steer);
			m_text_steer->SetPosition(glm::vec2(-390.0f, 350.0f));
			m_text_steer->SetScale(0.78f);
			m_text_steer->SetColor(glm::vec3(0.91f, 0.13f, 0.13f));

			if (player->GetScale() <= 0.13f)
			{
				// m_b_start = false;
				m_string_menu = "You're Burnt Out!";
				m_string_instruction = "Press 'R' to play again...";
				m_text_menu->SetText(m_string_menu);
				m_text_instruction->SetText(m_string_instruction);
				camera.SetPosX(0.0f);
				camera.SetPosY(0.0f);
				m_b_ended = true;
			}
			m_string_instruction = "Press: (1) Seek, (2) Arrive, (3) Containment, (4) Wander, (5) Flock, (6) Leader Follow";
			m_text_instruction->SetText(m_string_instruction);
			m_text_instruction->SetPosition(glm::vec2(-351.0f, -365.0f));
			m_text_instruction->SetColor(glm::vec3(0.26f, 0.0f, 0.26f));

			m_string_menu = "Press: (W), (A), (S), (D) to move the player.";
			m_text_menu->SetText(m_string_menu);
			m_text_menu->SetPosition(glm::vec2(-221, -390.0f));
			m_text_menu->SetColor(glm::vec3(0.78f, 0.0f, 0.26f));
		}

		m_clock->Process();
		player->m_currently_moved = false;
	}
	else
	{
		this->Initialize();
	}
}

bool GameManager::collision_check(float _top, float _bottom, float _left, float _right)
{
	// Check whether or not the position is occupied by an obstacle
	for (auto& gameObjects : m_vector_playerObjects)
	{
		for (auto& gameObjects2 : m_vector_obstacleObjects)
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
						gameObjects->Move(MOVE_DOWN, g_player_size + 1);
						camera.MovePosY(-2.0f);
					}
					else if (_bottom > 0)
					{
						gameObjects->Move(MOVE_UP, g_player_size + 1);
						camera.MovePosY(2.0f);
					}
					else if (_left > 0)
					{
						gameObjects->Move(MOVE_RIGHT, g_player_size + 1);
						camera.MovePosX(2.0f);
					}
					else if (_right > 0)
					{
						gameObjects->Move(MOVE_LEFT, g_player_size + 1);
						camera.MovePosX(-2.0f);
					}
				}
				return true;
			}
		}
	}
	
	return false;
}

void GameManager::Enemy_Collision_Check()
{
	// Check whether or not a position is occupied by a m_enemy_earth
	std::vector<Vehicle*>::iterator it_vec_game_object;
	for (auto& gameObjects : m_vector_playerObjects)
	{
		for (auto& gameObjects2 : m_vector_enemyEarth)
		{
			/*std::cout << gameObjects->GetPosition(RIGHT) << " >= " << gameObjects2->GetPosition(LEFT) << ", " << gameObjects->GetPosition(LEFT) << "<=" << gameObjects2->GetPosition(RIGHT);
			std::cout << " , " << gameObjects->GetPosition(BOTTOM) << " <= " << gameObjects2->GetPosition(TOP) << ", " << gameObjects->GetPosition(TOP) << ">=" << gameObjects2->GetPosition(BOTTOM);
			std::cout << std::endl;*/

			if (gameObjects->GetPosition(RIGHT) >= gameObjects2->GetPosition(LEFT)
				&& gameObjects->GetPosition(LEFT) <= gameObjects2->GetPosition(RIGHT)
				&& gameObjects->GetPosition(BOTTOM) <= gameObjects2->GetPosition(TOP)
				&& gameObjects->GetPosition(TOP) >= gameObjects2->GetPosition(BOTTOM))
			{
				std::cout << "m_enemy_earth found!" << std::endl;
				/*m_i_steer += 100;
				g_player_size += 0.02f;
				if (player->GetScale() <= 130)
				{
					player->Scale(player->GetScale() * g_player_size);
				}*/
				gameObjects2->Disable();
				m_vector_erasedEarth.push_back(gameObjects2);
				// if you remove it from the vector, it will not be deleted
				// but if you don't, it will still be checked every frame, and you will still collide with it
				it_vec_game_object = std::remove(m_vector_enemyEarth.begin(), m_vector_enemyEarth.end(), gameObjects2);
				// There I push it to another vector to keep it's address, so I can delete it at the end of the game
				m_vector_enemyEarth.erase(it_vec_game_object);
			}
		}
	}
}

void GameManager::Enemy_Collision_Check2()
{
	// Check whether or not a position is occupied by a m_enemy_earth
	std::vector<Vehicle*>::iterator it_vec_game_object;
	for (auto& gameObjects : m_vector_playerObjects)
	{
		for (auto& gameObjects2 : m_vector_enemyIce)
		{
			/*std::cout << gameObjects->GetPosition(RIGHT) << " >= " << gameObjects2->GetPosition(LEFT) << ", " << gameObjects->GetPosition(LEFT) << "<=" << gameObjects2->GetPosition(RIGHT);
			std::cout << " , " << gameObjects->GetPosition(BOTTOM) << " <= " << gameObjects2->GetPosition(TOP) << ", " << gameObjects->GetPosition(TOP) << ">=" << gameObjects2->GetPosition(BOTTOM);
			std::cout << std::endl;*/

			if (gameObjects->GetPosition(RIGHT) >= gameObjects2->GetPosition(LEFT)
				&& gameObjects->GetPosition(LEFT) <= gameObjects2->GetPosition(RIGHT)
				&& gameObjects->GetPosition(BOTTOM) <= gameObjects2->GetPosition(TOP)
				&& gameObjects->GetPosition(TOP) >= gameObjects2->GetPosition(BOTTOM))
			{
				std::cout << "m_enemy_earth found!" << std::endl;
				/*m_i_steer += 100;
				g_player_size -= 0.1f;
				if (player->GetScale() <= 130)
				{
					player->Scale(player->GetScale() * g_player_size);
				}*/
				gameObjects2->Disable();
				m_vector_erasedIce.push_back(gameObjects2);
				// if you remove it from the vector, it will not be deleted
				// but if you don't, it will still be checked every frame, and you will still collide with it
				it_vec_game_object = std::remove(m_vector_enemyIce.begin(), m_vector_enemyIce.end(), gameObjects2);
				// There I push it to another vector to keep it's address, so I can delete it at the end of the game
				m_vector_enemyIce.erase(it_vec_game_object);
			}
		}
	}
}

void GameManager::Render()
{
	if (m_b_initialized == 1)
	{
		// Drawing background
		for (auto& backgroundObjects : m_vector_backgroundObjects)
		{
			backgroundObjects->Draw(camera, "currentTime", currentTime);
		}

		// Drawing all players
		for (auto& playerObjects : m_vector_playerObjects)
		{
			playerObjects->Draw(camera, "currentTime", currentTime, "frameCounts", static_cast<int>(frameCounts));
		}

		// Drawing all obstacles
		for (auto& coinObjects2 : m_vector_enemyIce)
		{
			coinObjects2->Draw(camera, "currentTime", currentTime, "frameCounts", static_cast<int>(frameCounts));
		}
		
		// Drawing all obstacles
		for (auto& coinObjects : m_vector_enemyEarth)
		{
			coinObjects->Draw(camera, "currentTime", currentTime, "frameCounts", static_cast<int>(frameCounts));
		}

		// Draw all collectables
		for (auto& obstacleObjects : m_vector_obstacleObjects)
		{
			obstacleObjects->Draw(camera, "currentTime", currentTime);
		}

		//m_enemy_ice->Draw(camera, "currentTime", currentTime, "frameCounts", static_cast<int>(frameCounts));

		if (player->GetScale() <= 0.13f || m_b_start == 0)
		{
			Menu->Draw(camera, "currentTime", currentTime);
			player->Draw(camera, "currentTime", currentTime, "frameCounts", static_cast<int>(frameCounts));
			
			
		}
		
		if (m_text_steer != nullptr)
		{
			m_text_steer->Render();
		}

		// Render instruction
		m_text_instruction->Render();
		m_text_menu->Render();
		
		frameCounts += 1.0f * m_clock->GetDeltaTick() * 120.0f;
	}
	else
	{
		this->Initialize();
	}
}

bool GameManager::IsStarted()
{
	return m_b_start;
}

bool GameManager::IsEnded()
{
	return m_b_ended;
}

void GameManager::StartGame()
{
	m_b_start = true;
}

void GameManager::set_behaviour(behaviour steer)
{
	m_steering = steer;
}

void GameManager::change_behaviour_text()
{
	if (m_steering == SEEK)
	{
		m_string_steer = "Seek";
	}

	else if (m_steering == ARRIVE)
	{
		m_string_steer = "Arrive";
	}

	else if (m_steering == WANDER)
	{
		m_string_steer = "Wander";
	}

	else if (m_steering == CONTAINMENT)
	{
		m_string_steer = "Containment";
	}

	else if (m_steering == FLOCK)
	{
		m_string_steer = "Flock";
	}
	else if (m_steering == LEAD_FOLLOWING)
	{
		m_string_steer = "Leader Following";
	}
}

CClock * GameManager::GetClock()
{
	return m_clock;
}
