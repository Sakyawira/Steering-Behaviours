/***********************
  File Name   :   Clock.h
  Description :   contains prototype of clock which calculate the delta time between frames
  Author      :   Sakyawira Nanda Ruslim
  Mail        :   Sakyawira@gmail.com
********************/
#pragma once
// Library Includes
#include <chrono>
#include <vector>

class Clock
{
public:
	Clock();
	~Clock();
	bool Initialise();
	void Process();
	float GetDeltaTime();

protected:

private:
	Clock(const Clock& _kr);
	Clock& operator= (const Clock& _kr);

public:

protected:
	double timeElapsed;
	double deltaTime;
	std::chrono::high_resolution_clock::time_point lastTime;
	std::chrono::high_resolution_clock::time_point currentTime;

	std::vector<double> timeHistory;

	long long numCounts;

private:

};
