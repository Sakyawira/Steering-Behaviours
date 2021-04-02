/***********************
  File Name   :   Texture.h
  Description :   define the Texture class which contain functions to create a texture and store it within an instance of this class
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
public:
	Texture(const char * textureDir);
	~Texture() = default;
	GLuint GetID();

private:
	GLuint textureID;
};

