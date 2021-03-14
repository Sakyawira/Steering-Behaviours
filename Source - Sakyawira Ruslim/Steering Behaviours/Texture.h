/***********************
  File Name   :   Texture.h
  Description :   declare the Texture class
  Author      :   Sakyawira Nanda Ruslim
  Mail        :   Sakyawira@gmail.com
********************/
#pragma once
#include <glew.h>
#include <SOIL.h>
#include <vector>
#include <gtc/type_ptr.hpp>
#include "ShaderLoader.h"

class Texture
{
	//Square 1
public:
	Texture(const char * textureDir);
	~Texture() = default;
	GLuint GetID();

private:
	GLuint textureID;
};

