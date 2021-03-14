/***********************
  File Name   :   Camera.h
  Description :   declare and define the Camera class
  Author      :   Sakyawira Nanda Ruslim
  Mail        :   Sakyawira@gmail.com
********************/
#pragma once
#include <glew.h>
#include <vector>
#include <mat4x2.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.inl>

class Camera
{
public:
	Camera(unsigned int _screenWidth, unsigned int _screenHeight) 
	{
		screenWidth = _screenWidth;
		screenHeight = _screenHeight;
	};

	~Camera() = default;

	void UseCamera(GLuint program/*, glm::mat4 view, glm::mat4 proj*/)
	{
		// Put view matrix into '*program'
		GLuint viewLoc = glGetUniformLocation(program, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));

		// Put the Projection (Orthographic/Perspective) Matrix into '*program'
		GLuint projLoc = glGetUniformLocation(program, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, value_ptr(proj));
	}

	void CameraUpdate()
	{
		view = glm::lookAt(camPos, camPos + camLookDir, camUpDir);
	}

	void MovePosX(float i_magnitude)
	{
		camPos.x += (1.0f * i_magnitude);
	}
	void MovePosY(float i_magnitude)
	{
		camPos.y += (1.0f * i_magnitude);
	}
	void SetPosX(float i_magnitude)
	{
		camPos.x = i_magnitude;
	}
	void SetPosY(float i_magnitude)
	{
		camPos.y = i_magnitude;
	}
	
private:
	 // Camera
	 glm::vec3 camPos = glm::vec3(0.0f, 0.0f, 3.0f);
	 glm::vec3 camLookDir = glm::vec3(0.0f, 0.0f, -1.0f);
	 glm::vec3 camUpDir = glm::vec3(0.0f, 1.0f, 0.0f);

	 // View Matrix 
	 glm::mat4 view = glm::lookAt(camPos, camPos + camLookDir, camUpDir);

	 // Screen Size
	 unsigned int screenWidth = 800;
	 unsigned int screenHeight = 800;

	 float halfScreenWidth = (float)screenWidth * 0.5f;
	 float halfScreenHeight = (float)screenHeight * 0.5f;

	 // Orthographic
	 glm::mat4 proj = glm::ortho(-halfScreenWidth, halfScreenWidth, -halfScreenHeight, halfScreenHeight, 0.1f, 100.0f);
};
