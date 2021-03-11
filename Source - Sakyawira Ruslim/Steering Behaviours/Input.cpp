#include "Input.h"

void Input::ProcessInput(GameManager* Game)
{
	if (KeyState['w'] == INPUT_DOWN)
	{
		// use g_player_size
		// to check the collision from further away depends on the player size
		if (!Game->collision_check(Game->g_player_size + 1, 0, 0, 0) && Game->IsStarted())
		{
			Game->player->Move(MOVE_UP, 2 * Game->GetClock()->GetDeltaTick() * 120.0f);
			Game->camera.MovePosY(2.0f * Game->GetClock()->GetDeltaTick() * 120.0f);
			Game->player->m_currently_moved = true;
		}
	}
	if (KeyState['s'] == INPUT_DOWN)
	{
		// use g_player_size
		// to check the collision from further away depends on the player size
		if (!Game->collision_check(0, Game->g_player_size + 1, 0, 0) && Game->IsStarted())
		{
			Game->player->Move(MOVE_DOWN, 2 * Game->GetClock()->GetDeltaTick() * 120.0f);
			Game->camera.MovePosY(-2.0f * Game->GetClock()->GetDeltaTick() * 120.0f);
			Game->player->m_currently_moved = true;
		}
	}
	if (KeyState['d'] == INPUT_DOWN)
	{
		// use g_player_size
		// to check the collision from further away depends on the player size
		if (!Game->collision_check(0, 0, 0, Game->g_player_size + 1) && Game->IsStarted())
		{
			Game->player->Move(MOVE_RIGHT, 2 * Game->GetClock()->GetDeltaTick() * 120.0f);
			Game->camera.MovePosX(2.0f * Game->GetClock()->GetDeltaTick() * 120.0f);
			Game->player->m_currently_moved = true;
		}
	}
	if (KeyState['a'] == INPUT_DOWN)
	{
		// use g_player_size
		// to check the collision from further away depends on the player size
		if (!Game->collision_check(0, 0, Game->g_player_size + 1, 0) && Game->IsStarted())
		{
			Game->player->Move(MOVE_LEFT, 2 * Game->GetClock()->GetDeltaTick() * 120.0f);
			Game->camera.MovePosX(-2.0f * Game->GetClock()->GetDeltaTick() * 120.0f);
			Game->player->m_currently_moved = true;
		}
	}
	if (KeyState['r'] == INPUT_DOWN)
	{
		if (Game->IsEnded())
		{
			// Start working on initializing the game on restart instead of making a new one
			Game->Initialize();
		}

		else if (!Game->IsStarted() && !Game->IsEnded())
		{
			Game->StartGame();
		}
	}
	if (KeyState['1'] == INPUT_DOWN)
	{
		Game->set_behaviour(SEEK);
		Game->change_behaviour_text();
	}
	else if (KeyState['2'] == INPUT_DOWN)
	{
		Game->set_behaviour(ARRIVE);
		Game->change_behaviour_text();
	}
	else if (KeyState['3'] == INPUT_DOWN)
	{
		Game->set_behaviour(CONTAINMENT);
		Game->change_behaviour_text();
	}
	else if (KeyState['4'] == INPUT_DOWN)
	{
		Game->set_behaviour(WANDER);
		Game->change_behaviour_text();
	}
	else if (KeyState['5'] == INPUT_DOWN)
	{
		Game->set_behaviour(FLOCK);
		Game->change_behaviour_text();
	}
	else if (KeyState['6'] == INPUT_DOWN)
	{
		Game->set_behaviour(LEAD_FOLLOWING);
		Game->change_behaviour_text();
	}
}

glm::vec3 Input::GetLocation()
{
	return m_mouse_location;
}
