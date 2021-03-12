#pragma once
#include <iostream>
#include "GameManager.h"
#include <freeglut.h>
#include "clock.h"

class Input
{
public:
	Input() = default;
	~Input() = default;

	void ProcessInput(GameManager* Game);
	void MouseClick(int button, int state, int x, int y);
	void MousePassiveMove(int x, int y);
	void MouseMove(int x, int y) {}
	void KeyboardDown(unsigned char key, int x, int y);
	void KeyboardUp(unsigned char key, int x, int y);
	glm::vec3 GetLocation();

private:

	// Define Input
	enum InputState
	{
		INPUT_UP,
		INPUT_DOWN,
		INPUT_UP_FIRST,
		INPUT_DOWN_FIRST,
	};

	// Input Container
	InputState KeyState[255];
	InputState MouseState[3];
	glm::vec3 m_mouse_location = glm::vec3(0.0f, 0.0f, 0.0f);
};


