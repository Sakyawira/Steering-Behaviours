#include "Initialization.h"
#include "TextLabel.h"
#include <iostream>
#include <chrono>
#include <ctime>   
#include <random>

/***********************
 Description :   Loads main scene and activates loading screen
********************/
int main(int argc, char **argv)
{
	auto start = std::chrono::system_clock::now();
	std::time_t t = std::chrono::system_clock::to_time_t(start);
	std::time_t* iTime = new time_t(t);
	srand(static_cast<unsigned int>(time(iTime)));
	delete iTime;

	audio.Load();
	// audio.Play(SOUND_BGM1);
		
	// Setup and create at glut controlled window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("OpenGL First Window");

	// Sets up all gl function callbacks based on pc hardware

	if (glewInit() != GLEW_OK)
	{
		// If glew setup failed then application will not run graphics correctly
		// std::cout << "Glew Initialization Failed. Aborting Application." << std::endl;
		system("pause");
	}

	// Set the clear color when calling glClear()
	glClearColor(0.0, 0.0, 0.0, 1.0); // Red

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

	Game = new GameManager();
	//	Game->Initialize();
	
	//Register callbacks
	glutDisplayFunc(Render);
	glutIdleFunc(Update);

	glutKeyboardFunc(KeyboardDown);
	glutKeyboardUpFunc(KeyboardUp);

	glutMouseFunc(MouseClick);
	glutMotionFunc(MouseMove);
	glutPassiveMotionFunc(MousePassiveMove);

	//glutCloseFunc(ShutDown);
	glutMainLoop(); //Ensure this is the last glut line called

	ShutDown();

	return 0;
}

/***********************
 Description :   Loads main scene and activates loading screen
********************/
void Update()
{
	//FMOD_RESULT System::update();
	audio.Update();

	// Process Game
	Game->ProcessGame(audio, input.GetMousePosition());
	// Process Input
	input.ProcessInput(Game);
	// Update game information
	glutPostRedisplay();
}

/***********************
 Description :   Loads main scene and activates loading screen
********************/
void Render()
{
	glClear((GL_COLOR_BUFFER_BIT));

	// Swap culling
	/*glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);*/
	if (Game != nullptr)
	{
		Game->Render();
	}

	glutSwapBuffers();
}

/***********************
 Description :   Loads main scene and activates loading screen
********************/
void ShutDown()
{
	delete Game;
}

/***********************
 Description :   Loads main scene and activates loading screen
********************/
void KeyboardUp(unsigned char key, int x, int y)
{
	input.KeyboardUp(key, x, y);
}

/***********************
 Description :   Loads main scene and activates loading screen
********************/
void KeyboardDown(unsigned char key, int x, int y)
{
	input.KeyboardDown(key, x, y);
}

/***********************
 Description :   Loads main scene and activates loading screen
********************/
void MouseClick(int button, int state, int x, int y)
{
	input.MouseClick(button, state, x, y);
}

/***********************
 Description :   Loads main scene and activates loading screen
********************/
void MousePassiveMove(int x, int y)
{
	input.MousePassiveMove(x, y);
}

/***********************
 Description :   Loads main scene and activates loading screen
********************/
void MouseMove(int x, int y)
{
	input.MouseMove(x, y);
}
