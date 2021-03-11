#include "Initialization.h"
#include "TextLabel.h"
#include <random>

void Update()
{
	//FMOD_RESULT System::update();
	audio.Update();

	// Process Game
	Game->ProcessGame(audio, input.GetLocation());
	
	// Process Input
	input.ProcessInput(Game);
	
	// Update game information
	glutPostRedisplay();
}

void KeyboardUP(unsigned char key, int x, int y)
{
	input.KeyboardUp(key, x, y);
}

void KeyboardDOWN(unsigned char key, int x, int y)
{
	input.KeyboardDown(key, x, y);
}

void MouseClick(int button, int state, int x, int y)
{
	input.MouseClick(button, state, x, y);
}

void MousePassiveMove(int x, int y)
{
	input.MousePassiveMove(x, y);
}

void MouseMove(int x, int y)
{
	input.MouseMove(x, y);
}

int main(int argc, char **argv)
{
	//assert(AudioInit() == true);
	audio.Load();
	// audio.Play(SOUND_BGM1); 
	//audio.Play(SOUND_VICTORY);
		
	// Setup and create at glut controlled window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(WINDOW_WIDHT, WINDOW_HEIGHT);
	glutCreateWindow("OpenGL First Window");

	// Sets up all gl function callbacks based on pc hardware

	if (glewInit() != GLEW_OK)
	{
		// If glew setup failed then application will not run graphics correctly
		std::cout << "Glew Initialization Failed. Aborting Application." << std::endl;
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

	glutKeyboardFunc(KeyboardDOWN);
	glutKeyboardUpFunc(KeyboardUP);

	glutMouseFunc(MouseClick);
	glutMotionFunc(MouseMove);
	glutPassiveMotionFunc(MousePassiveMove);

	//glutCloseFunc(ShutDown);
	glutMainLoop(); //Ensure this is the last glut line called

	ShutDown();

	return 0;
}

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

void ShutDown()
{
	delete Game;
}
