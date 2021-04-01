/***********************
  File Name   :   Clock.cpp
  Description :   Class definition of Clock, calcualtes the delta time between frames
  Author      :   Sakyawira Nanda Ruslim
  Mail        :   Sakyawira@gmail.com
********************/
// Library Includes
#include <chrono>
// This Includes
#include "Clock.h"


/***********************
 Description :   Constructor, initialise time elapsed and delta time to 0
********************/
Clock::Clock()
{
	timeElapsed = 0.0f;
	deltaTime = 0.0f;
}

/***********************
 Description :   Destructor
********************/
Clock::~Clock()
{

}

/***********************
 Description :   Sets the first time values, return true if succesful
********************/
bool Clock::Initialise()
{
	currentTime = std::chrono::high_resolution_clock::now();
	return (true);
}

/***********************
 Description :   Processes the change in time since it was last called
********************/
void Clock::Process()
{
	lastTime = currentTime;

	currentTime = std::chrono::high_resolution_clock::now();


	deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTime).count();

	timeElapsed += deltaTime;
}

/***********************
 Description :   Gets the current delta time value
********************/
float Clock::GetDeltaTime()
{
	return (deltaTime);
}