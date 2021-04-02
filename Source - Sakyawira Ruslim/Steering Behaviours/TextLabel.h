/***********************
  File Name   :   TextLabel.h
  Description :   Declaration of a class used for configuring and rendering texts
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
#include <ft2build.h>
#include FT_FREETYPE_H

// Library Includes
#include <iostream>
#include <vector>
#include <assert.h>

// Local Includes
#include "ShaderLoader.h"
#include "Camera.h"
#include "glm.hpp"

struct FontChar
{
	GLuint TextureID;	// Texture ID
	glm::ivec2 Size;	// Size of the glyph
	glm::ivec2 Bearing; // Offset of the glyph (top left) from the baseline
	GLuint Advance;
};

class TextLabel
{
	public:
		TextLabel(
			int _WINDOW_WIDTH,
			int _WINDOW_HEIGHT,
			std::string _text,
			std::string _font,
			glm::vec2 _pos,
			glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f),
			float _scale = 1.0f
		);
	
		~TextLabel() {};
	
		void Render();
		void SetText(std::string _text) { text = _text; };
		void SetColor(glm::vec3 _color) { color = _color; };
		void SetScale(GLfloat _scale) { scale = _scale; };
		void SetPosition(glm::vec2 _position) { position = _position; };
	
	private:
		GLuint generateTexture(FT_Face _face);

		std::string text;
		GLfloat scale;
		glm::vec3 color;
		glm::vec2 position;

		GLuint VAO, VBO, program;
		glm::mat4 proj;
		std::map<GLchar, FontChar> characters;
};