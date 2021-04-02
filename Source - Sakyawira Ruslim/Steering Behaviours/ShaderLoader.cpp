/***********************
  File Name   :   ShaderLoader.h
  Description :   Contains definition of a singleton helper class that loads shaders and attach them to a program
  Author      :   Sakyawira Nanda Ruslim
  Mail        :   Sakyawira@gmail.com
********************/
#include "ShaderLoader.h" 
#include<iostream>
#include<fstream>
#include<vector>

/***********************
 Description :   Return a singleton instance
********************/
ShaderLoader& ShaderLoader::GetInstance()
{
	static ShaderLoader instance;
							 
	return instance;
}

/***********************
 Description :   Creates a program and attach the shaders to it
********************/
GLuint ShaderLoader::CreateProgram(const char* _vertexShaderFilename, const char* _fragmentShaderFilename)
{
	// Create program attach the shader(s) to it
	GLuint program = glCreateProgram();

	const GLuint vertexShaderID = createShader(GL_VERTEX_SHADER, _vertexShaderFilename);
	const GLuint fragmentShaderID = createShader(GL_FRAGMENT_SHADER, _fragmentShaderFilename);
	std::string combinedShader = std::to_string(vertexShaderID) + std::to_string(fragmentShaderID);

	for (auto &pair : GetInstance().shaderMap)
	{
		if (combinedShader == pair.second)
		{
			// std::cout << "We found the same combined pair!" << std::endl;
			return pair.first;
		}
	}

	glAttachShader(program,vertexShaderID);
	glAttachShader(program,fragmentShaderID);

	// Linking the program
	glLinkProgram(program);

	// Check for link errors
	int link_result = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &link_result);
	if (link_result == GL_FALSE)
	{
		std::string programName = _vertexShaderFilename + *_fragmentShaderFilename;
		printErrorDetails(false, program, programName.c_str());
		return 0;
	}

	GetInstance().shaderMap.insert({ program, combinedShader });

	return program;
}

/***********************
 Description :   Reads and compile shader, return a shaderId
********************/
GLuint ShaderLoader::createShader(GLenum _shaderType, const char* _shaderName)
{
	// Create a shaderID object based on the passed in types
	GLuint shaderID = glCreateShader(_shaderType);

	// Read the shader files and save it as a string
	std::string shaderSource = readShaderFile(_shaderName);

	for (auto &pair : GetInstance().shaderMap)
	{
		if (shaderSource == pair.second)
		{
			// std::cout << "We found the same pair!" << std::endl;
			return pair.first;
		}
	}

	// Convert shaderSource into a const char* and assign it to a const char*
	const char* cShaderSource = shaderSource.c_str();

	// Get the size of the string
	const int ShaderLength = shaderSource.size();

	// Populate the shaderID object
	glShaderSource(shaderID, 1, &cShaderSource, &ShaderLength);

	// Compile the shaderID
	glCompileShader(shaderID);

	// Check for errors
	int compile_result = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compile_result);
	if (compile_result == GL_FALSE)
	{
		printErrorDetails(true, shaderID, _shaderName);
		return 0;
	}

	GetInstance().shaderMap.insert({ shaderID, shaderSource });

	return shaderID;
}

/***********************
 Description :   Reads the shader file
********************/
std::string ShaderLoader::readShaderFile(const char *_filename)
{
	// Open the file for reading
	std::ifstream file(_filename, std::ios::in);
	std::string shaderCode;

	// Ensure the file is open and readable
	if (!file.good()) {
		// std::cout << "Cannot read file:  " << filename << std::endl;
		return "";
	}

	// Determine the size of of the file in characters and resize the string variable to accomodate
	file.seekg(0, std::ios::end);
	shaderCode.resize(static_cast<unsigned int>(file.tellg()));

	// Set the position of the next character to be read back to the beginning
	file.seekg(0, std::ios::beg);
	// Extract the contents of the file and store in the string variable
	file.read(&shaderCode[0], shaderCode.size());
	file.close();
	return shaderCode;
}

/***********************
 Description :   Prints the details for when compiling a shader fails
********************/
void ShaderLoader::printErrorDetails(bool _isShader, GLuint _id, const char* _name)
{
	int infoLogLength = 0;
	// Retrieve the length of characters needed to contain the info log
	(_isShader) ? glGetShaderiv(_id, GL_INFO_LOG_LENGTH, &infoLogLength) : glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &infoLogLength);
	std::vector<char> log(infoLogLength);

	// Retrieve the log info and populate log variable
	(_isShader) ? glGetShaderInfoLog(_id, infoLogLength, NULL, &log[0]) : glGetProgramInfoLog(_id, infoLogLength, NULL, &log[0]);		
	// std::cout << "Error compiling " << ((isShader) ? "shader" : "program") << ": " << name << std::endl;
	// std::cout << &log[0] << std::endl;
}