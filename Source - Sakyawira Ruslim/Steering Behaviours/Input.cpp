#include "Input.h"

void Input::ProcessInput(GameManager* Game)
{
	if (KeyState['w'] == INPUT_DOWN)
	{
		// use g_player_size
		// to check the collision from further away depends on the player size
		if (!Game->CollisionCheck(Game->playerSize + 1, 0, 0, 0) && Game->IsStarted())
		{
			Game->player->Move(MOVE_UP, 2 * Game->GetClock()->GetDeltaTick() / 10.0f);
			Game->camera->MovePosY(2.0f * Game->GetClock()->GetDeltaTick() / 10.0f);
			Game->player->currentlyMoved = true;
		}
	}
	if (KeyState['s'] == INPUT_DOWN)
	{
		// use g_player_size
		// to check the collision from further away depends on the player size
		if (!Game->CollisionCheck(0, Game->playerSize + 1, 0, 0) && Game->IsStarted())
		{
			Game->player->Move(MOVE_DOWN, 2 * Game->GetClock()->GetDeltaTick() / 10.0f);
			Game->camera->MovePosY(-2.0f * Game->GetClock()->GetDeltaTick() / 10.0f);
			Game->player->currentlyMoved = true;
		}
	}
	if (KeyState['d'] == INPUT_DOWN)
	{
		// use g_player_size
		// to check the collision from further away depends on the player size
		if (!Game->CollisionCheck(0, 0, 0, Game->playerSize + 1) && Game->IsStarted())
		{
			Game->player->Move(MOVE_RIGHT, 2 * Game->GetClock()->GetDeltaTick() / 10.0f);
			Game->camera->MovePosX(2.0f * Game->GetClock()->GetDeltaTick() / 10.0f);
			Game->player->currentlyMoved = true;
		}
	}
	if (KeyState['a'] == INPUT_DOWN)
	{
		// use g_player_size
		// to check the collision from further away depends on the player size
		if (!Game->CollisionCheck(0, 0, Game->playerSize + 1, 0) && Game->IsStarted())
		{
			Game->player->Move(MOVE_LEFT, 2 * Game->GetClock()->GetDeltaTick() / 10.0f);
			Game->camera->MovePosX(-2.0f * Game->GetClock()->GetDeltaTick() / 10.0f);
			Game->player->currentlyMoved = true;
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
		Game->SetBehaviour(SEEK);
		Game->ChangeBehaviourText();
	}
	else if (KeyState['2'] == INPUT_DOWN)
	{
		Game->SetBehaviour(ARRIVE);
		Game->ChangeBehaviourText();
	}
	else if (KeyState['3'] == INPUT_DOWN)
	{
		Game->SetBehaviour(CONTAINMENT);
		Game->ChangeBehaviourText();
	}
	else if (KeyState['4'] == INPUT_DOWN)
	{
		Game->SetBehaviour(WANDER);
		Game->ChangeBehaviourText();
	}
	else if (KeyState['5'] == INPUT_DOWN)
	{
		Game->SetBehaviour(FLOCK);
		Game->ChangeBehaviourText();
	}
	else if (KeyState['6'] == INPUT_DOWN)
	{
		Game->SetBehaviour(LEAD_FOLLOWING);
		Game->ChangeBehaviourText();
	}
}

void Input::MouseClick(int button, int state, int x, int y)
{
	if (button >= 3)
	{
		return;
	}
	MouseState[button] = (state == GLUT_DOWN) ? INPUT_DOWN : INPUT_UP;
}

void Input::MousePassiveMove(int x, int y)
{
	m_mouse_location = glm::vec3(x - 400.0f, -y + 400.0f, 0.0f);
}

void Input::KeyboardDown(unsigned char key, int x, int y)
{
	KeyState[key] = INPUT_DOWN;
}

void Input::KeyboardUp(unsigned char key, int x, int y)
{
	KeyState[key] = INPUT_UP;
}

glm::vec3 Input::GetLocation()
{
	return m_mouse_location;
}
