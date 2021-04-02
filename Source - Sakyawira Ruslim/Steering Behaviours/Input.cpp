#include "Input.h"

/***********************
 Description :   Checks for input state every frame
********************/
void Input::ProcessInput(GameManager* Game)
{
	if (keyState['w'] == InputState::INPUT_DOWN)
	{
		// to check the collision from further away
		if (!Game->CollisionCheck(Game->PlayerSize + 1, 0, 0, 0) && Game->IsStarted())
		{
			Game->Player->Move(MoveDirection::MOVE_UP, 2 * Game->GetClock()->GetDeltaTime() / 10.0f);
			Game->GameCamera->MovePosY(2.0f * Game->GetClock()->GetDeltaTime() / 10.0f);
			Game->Player->CurrentlyMoved = true;
		}
	}
	if (keyState['s'] == InputState::INPUT_DOWN)
	{
		// to check the collision from further away
		if (!Game->CollisionCheck(0, Game->PlayerSize + 1, 0, 0) && Game->IsStarted())
		{
			Game->Player->Move(MoveDirection::MOVE_DOWN, 2 * Game->GetClock()->GetDeltaTime() / 10.0f);
			Game->GameCamera->MovePosY(-2.0f * Game->GetClock()->GetDeltaTime() / 10.0f);
			Game->Player->CurrentlyMoved = true;
		}
	}
	if (keyState['d'] == InputState::INPUT_DOWN)
	{
		// to check the collision from further away
		if (!Game->CollisionCheck(0, 0, 0, Game->PlayerSize + 1) && Game->IsStarted())
		{
			Game->Player->Move(MoveDirection::MOVE_RIGHT, 2 * Game->GetClock()->GetDeltaTime() / 10.0f);
			Game->GameCamera->MovePosX(2.0f * Game->GetClock()->GetDeltaTime() / 10.0f);
			Game->Player->CurrentlyMoved = true;
		}
	}
	if (keyState['a'] == InputState::INPUT_DOWN)
	{
		// to check the collision from further away
		if (!Game->CollisionCheck(0, 0, Game->PlayerSize + 1, 0) && Game->IsStarted())
		{
			Game->Player->Move(MoveDirection::MOVE_LEFT, 2 * Game->GetClock()->GetDeltaTime() / 10.0f);
			Game->GameCamera->MovePosX(-2.0f * Game->GetClock()->GetDeltaTime() / 10.0f);
			Game->Player->CurrentlyMoved = true;
		}
	}
	if (keyState['r'] == InputState::INPUT_DOWN)
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
	if (keyState['1'] == InputState::INPUT_DOWN)
	{
		Game->SetBehaviour(SEEK);
		Game->ChangeBehaviourText();
	}
	else if (keyState['2'] == InputState::INPUT_DOWN)
	{
		Game->SetBehaviour(ARRIVE);
		Game->ChangeBehaviourText();
	}
	else if (keyState['3'] == InputState::INPUT_DOWN)
	{
		Game->SetBehaviour(CONTAINMENT);
		Game->ChangeBehaviourText();
	}
	else if (keyState['4'] == InputState::INPUT_DOWN)
	{
		Game->SetBehaviour(WANDER);
		Game->ChangeBehaviourText();
	}
	else if (keyState['5'] == InputState::INPUT_DOWN)
	{
		Game->SetBehaviour(FLOCK);
		Game->ChangeBehaviourText();
	}
	else if (keyState['6'] == InputState::INPUT_DOWN)
	{
		Game->SetBehaviour(LEAD_FOLLOWING);
		Game->ChangeBehaviourText();
	}
}

/***********************
 Description :   Callback function for when mouse is clicked
********************/
void Input::MouseClick(int button, int state, int x, int y)
{
	if (button >= 3)
	{
		return;
	}
	mouseState[button] = (state == GLUT_DOWN) ? InputState::INPUT_DOWN : InputState::INPUT_UP;
}

/***********************
 Description :   Sets the mouse location
********************/
void Input::MousePassiveMove(int x, int y)
{
	mousePosition = glm::vec3(x - windowWidth/2, -y + windowHeight/2, 0.0f);
}

/***********************
 Description :   Sets the state of a keyboard key to pressed down
********************/
void Input::KeyboardDown(unsigned char key, int x, int y)
{
	keyState[key] = InputState::INPUT_DOWN;
}

/***********************
 Description :   Sets the state of a keyboard key to released
********************/
void Input::KeyboardUp(unsigned char key, int x, int y)
{
	keyState[key] = InputState::INPUT_UP;
}

/***********************
 Description :   Gets the location of the mouse
********************/
glm::vec3 Input::GetMousePosition()
{
	return mousePosition;
}