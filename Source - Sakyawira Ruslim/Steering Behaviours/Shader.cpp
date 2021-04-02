/***********************
  File Name   :   Shader.cpp
  Description :   define the Shader class' constructor and functions
  Author      :   Sakyawira Nanda Ruslim
  Mail        :   Sakyawira@gmail.com
********************/
#include "Shader.h"

/***********************
 Description :   Creates a program using vertex shader and fragment shader
********************/
Shader::Shader(const char * _vertexShaderFilename, const char * _fragmentShaderFilename)
{
	program = ShaderLoader::CreateProgram(_vertexShaderFilename, _fragmentShaderFilename);
}

/***********************
 Description :   Updates the transform uniforms of the program with the object's transform
********************/
void Shader::Transform(glm::mat4 _translationMatrix, glm::mat4 _rotationZ, glm::mat4 _scaleMatrix, glm::mat4 _modelMatrix)
{
	// Put translation uniform into '*program'
	GLuint translateLoc = glGetUniformLocation(program, "translation");
	glUniformMatrix4fv(translateLoc, 1, GL_FALSE, glm::value_ptr(_translationMatrix));

	// Put rotation uniform into '*program'
	GLuint rotationLoc = glGetUniformLocation(program, "rotation");
	glUniformMatrix4fv(rotationLoc, 1, GL_FALSE, glm::value_ptr(_rotationZ));

	// Put scaling uniform into '*program'
	GLuint scaleLoc = glGetUniformLocation(program, "scale");
	glUniformMatrix4fv(scaleLoc, 1, GL_FALSE, glm::value_ptr(_scaleMatrix));

	// Put model uniform into '*program'
	GLuint modelLoc = glGetUniformLocation(program, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(_modelMatrix));
}

/***********************
 Description :   Pass the textures of the object to the shader as uniforms
********************/
void Shader::PassTexture(std::vector<Texture*> _textures)
{
	std::string textureUniform = "tex";
	unsigned int textureNumber = 0;
	// rendering texture "texture"
	for (auto texture : _textures)
	{
		glActiveTexture(GL_TEXTURE0 + textureNumber);
		glBindTexture(GL_TEXTURE_2D, texture->GetID());
		const GLchar* name = textureUniform.c_str();
		glUniform1i(glGetUniformLocation(program, name), textureNumber);
		textureNumber++;
		textureUniform += std::to_string(textureNumber);
	}
}

/***********************
 Description :   Passes a generic float uniform to the program
********************/
void Shader::PassUniform(const GLchar * _name, GLfloat _float)
{
	GLint currentTimeLoc = glGetUniformLocation(program, _name);
	glUniform1f(currentTimeLoc, _float);
}

/***********************
 Description :   Passes a generic int uniform to the program
********************/
void Shader::PassUniform(const GLchar * _name, GLint _int)
{
	GLint frameCountsLoc = glGetUniformLocation(program, _name);
	glUniform1i(frameCountsLoc, _int);
}

/***********************
 Description :   Use this program (shaders) to draw the next object
********************/
void Shader::Activate()
{
	glUseProgram(program);
}

/***********************
 Description :   Return the program
********************/
GLuint Shader::GetProgram()
{
	return program;
}
