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

	void MouseClick(int button, int state, int x, int y)
	{
		if (button >= 3)
		{
			return;
		}

		MouseState[button] = (state == GLUT_DOWN) ? INPUT_DOWN : INPUT_UP;
		std::cout << "Clicked Once x: " << x << " | y: " << y << std::endl;
	}

	void MousePassiveMove(int x, int y)
	{
		std::cout << "Passive x: " << x << " | y: " << y << std::endl;
		m_mouse_location = glm::vec3(x - 400.0f, - y + 400.0f, 0.0f);
	}

	void MouseMove(int x, int y)
	{
		std::cout << "Clicked x: " << x << " | y: " << y << std::endl;
	}
	void KeyboardDown(unsigned char key, int x, int y)
	{
		KeyState[key] = INPUT_DOWN;
	}

	void KeyboardUp(unsigned char key, int x, int y)
	{
		KeyState[key] = INPUT_UP;
	}

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


