/***********************
  Bachelor of Software Engineering
  Media Design School
  Auckland
  New Zealand

  (c) 2018 Media Design School

  File Name   :   Camera.h
  Description :   declare and define the Camera class
  Author      :   Sakyawira Nanda Ruslim
  Mail        :   Sakyawira.Rus8080@mediadesign.school.nz
********************/
#pragma once
#include <glew.h>
#include <vector>
#include <mat4x2.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.inl>

class Camera
{
	//Square 1
public:
	Camera() = default;
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

	/// View Matrix 
	glm::mat4 view = glm::lookAt(camPos, camPos + camLookDir, camUpDir);

	// Screen Size
	 unsigned int SCR_WIDTH = 800;
	 unsigned int SCR_HEIGHT = 800;

	 float halfScreenWidth = (float)SCR_WIDTH * 0.5f;
	 float halfScreenHeight = (float)SCR_HEIGHT * 0.5f;

	// Projection Space

		// Perspective
			/*glm::mat4 proj = glm::perspective(45.0f, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);*/

		// Orthographic
	 glm::mat4 proj = glm::ortho(-halfScreenWidth, halfScreenWidth, -halfScreenHeight, halfScreenHeight, 0.1f, 100.0f);
};
