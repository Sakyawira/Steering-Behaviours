/***********************
  File Name   :   Initialization.h
  Description :   declare all the global variables and dependency includes
  Author      :   Sakyawira Nanda Ruslim
  Mail        :   Sakyawira@gmail.com
********************/
#pragma once

// Dependency Includes
#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>
#include <glm.hpp>
#include <fmod.hpp>
// #include <vld.h>

// Library Includes
#include <iostream>
#include <vector>
#include <assert.h>

// Local Includes
#include "ShaderLoader.h"
#include "GameObject.h"
#include "Camera.h"
#include "glm.hpp"
#include "TextLabel.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Audio.h"
#include "Vehicle.h"
#include "Input.h"

Audio audio;

Input input;

GameManager* Game;

void Render();

void ShutDown();