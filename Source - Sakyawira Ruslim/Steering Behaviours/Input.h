#pragma once
#include <iostream>
#include "GameManager.h"
#include <freeglut.h>
#include "Clock.h"

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
	glm::vec3 GetMousePosition();

private:

	// Define Input
	enum class InputState
	{
		INPUT_UP,
		INPUT_DOWN,
		INPUT_UP_FIRST,
		INPUT_DOWN_FIRST,
	};

	// Input Container
	InputState keyState[255];
	InputState mouseState[3];
	glm::vec3 mousePosition = glm::vec3(0.0f, 0.0f, 0.0f);
};