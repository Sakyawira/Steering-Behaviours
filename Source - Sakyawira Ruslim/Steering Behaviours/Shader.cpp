/***********************
  File Name   :   Shader.cpp
  Description :   define the Shader class' constructor and functions
  Author      :   Sakyawira Nanda Ruslim
  Mail        :   Sakyawira@gmail.com
********************/
#include "Shader.h"

/***********************
 Description :   Loads main scene and activates loading screen
********************/
Shader::Shader(const char * VertexShaderFilename, const char * FragmentShaderFilename)
{
	m_program = ShaderLoader::CreateProgram(VertexShaderFilename, FragmentShaderFilename);
}

/***********************
 Description :   Loads main scene and activates loading screen
********************/
void Shader::Transform(glm::mat4 translationMatrix, glm::mat4 rotationZ, glm::mat4 scaleMatrix, glm::mat4 modelMatrix)
{
	// Put translation uniform into '*program'
	GLuint translateLoc = glGetUniformLocation(m_program, "translation");
	glUniformMatrix4fv(translateLoc, 1, GL_FALSE, glm::value_ptr(translationMatrix));

	// Put rotation uniform into '*program'
	GLuint rotationLoc = glGetUniformLocation(m_program, "rotation");
	glUniformMatrix4fv(rotationLoc, 1, GL_FALSE, glm::value_ptr(rotationZ));

	// Put scaling uniform into '*program'
	GLuint scaleLoc = glGetUniformLocation(m_program, "scale");
	glUniformMatrix4fv(scaleLoc, 1, GL_FALSE, glm::value_ptr(scaleMatrix));


	// Put model uniform into '*program'
	GLuint modelLoc = glGetUniformLocation(m_program, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
}

/***********************
 Description :   Loads main scene and activates loading screen
********************/
void Shader::PassTexture(std::vector<Texture*> v_texture)
{
	std::string textureUniform = "tex";
	unsigned int textureNumber = 0;
	// rendering texture "texture"
	for (auto texture: v_texture)
	{
		glActiveTexture(GL_TEXTURE0 + textureNumber);
		glBindTexture(GL_TEXTURE_2D, texture->GetID());
		const GLchar* name = textureUniform.c_str();
		glUniform1i(glGetUniformLocation(m_program, name), textureNumber);
		textureNumber++;
		textureUniform += std::to_string(textureNumber);
	}

	//// Get texture to render
	//glActiveTexture(GL_TEXTURE1);
	//glBindTexture(GL_TEXTURE_2D, v_texture2->GetID());
	//glUniform1i(glGetUniformLocation(m_program, "tex1"), 1);
}

/***********************
 Description :   Loads main scene and activates loading screen
********************/
void Shader::PassUniform(const GLchar * name, GLfloat _float)
{
	GLint currentTimeLoc = glGetUniformLocation(m_program, name);
	glUniform1f(currentTimeLoc, _float);
}

/***********************
 Description :   Loads main scene and activates loading screen
********************/
void Shader::PassFrameUniform(const GLchar * name, GLint _int)
{
	GLint frameCountsLoc = glGetUniformLocation(m_program, name);
	glUniform1i(frameCountsLoc, _int);
}

/***********************
 Description :   Loads main scene and activates loading screen
********************/
void Shader::Activate()
{
	glUseProgram(m_program);
}

/***********************
 Description :   Loads main scene and activates loading screen
********************/
GLuint Shader::GetProgram()
{
	return m_program;
}
