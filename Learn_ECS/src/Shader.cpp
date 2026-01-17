/*************************************************************//**
 * @file   Shader.cpp
 * @brief  Function definitions for a shader program
 *
 * Key features:
 * Create a shader program
 * Add uniform to map for reduced look up time
 *
 * Usage:
 *
 * Dependencies:
 *
 * @author HONG Xian Xiang
 * @date   31st October 2024
 * Copyright 2024, Digipen Institute of Technology
*****************************************************************/

#include <fstream>
#include <sstream>
#include <iostream>
#include "Shader.hpp"

std::unordered_map<std::string, Shader> Shader::mStringToShaderMap;

/**
 * @brief Ctor to create a shader program
 * @param[in] vertShaderPath Path to the vertex shader
 * @param[in] fragShaderPath Path to the fragment shader
 */
Shader::Shader(std::string const& vertShaderPath, std::string const& fragShaderPath)
{
	GLint success;
	char infoLog[512];

	// Vertex Shader
	std::string vertShaderStr{ Shader::ReadShaderFile(vertShaderPath) };
	char const* vertShaderCharPtr{ vertShaderStr.c_str() };
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertShaderCharPtr, nullptr);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::cout << "Failed to compile vertex shader.\n";
		std::cout << infoLog << '\n';
		return;
	}

	// Fragment Shader
	std::string fragShaderStr{ Shader::ReadShaderFile(fragShaderPath) };
	char const* fragShaderCharPtr{ fragShaderStr.c_str() };
	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragShaderCharPtr, nullptr);
	glCompileShader(fragShader);
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragShader, 512, nullptr, infoLog);
		std::cout << "Failed to compile fragment shader.\n";
		std::cout << infoLog << '\n';
		return;
	}

	// Link and compile
	mId = glCreateProgram();
	glAttachShader(mId, vertexShader);
	glAttachShader(mId, fragShader);
	glLinkProgram(mId);
	glGetProgramiv(mId, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(mId, 512, nullptr, infoLog);
		std::cout << "Failed to link shaders.\n";
		std::cout << infoLog << '\n';
		return;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);
}

/**
 * @brief Returns the shader program's handle
 * @return The shader program's handle
 */
GLint Shader::GetId() const
{
	return mId;
}

/**
 * @brief Add a uniform and its location to a map to reduce look up time
 * @param[in] uniformName Name of the uniform
 */
void Shader::AddUniform(std::string const& uniformName)
{
	char const* uniformNameCharPtr{ uniformName.c_str() };
	mUniformToLocationMap[uniformName] = glGetUniformLocation(mId, uniformNameCharPtr);
}

/**
 * @brief Set a uniform for a 3x3 matrix
 * @param[in] uniformName Name of the uniform
 * @param[in] value Value of the uniform in the shader
 */
void Shader::SetUniform(std::string const& uniformName, GLfloat const* value)
{
	// TODO ambiguous function. Can be used for Matrix4fv
	glUniformMatrix3fv(mUniformToLocationMap[uniformName], 1, GL_FALSE, value);
}

/**
 * @brief Set a uniform for an array of ints
 * @param[in] uniformName Name of the uniform
 * @param[in] count Number of ints
 * @param[in] value Pointer to the array of ints
 */
void Shader::SetUniform(std::string const& uniformName, GLsizei count, GLint const* value)
{
	glUniform1iv(mUniformToLocationMap[uniformName], count, value);
}

/**
 * @brief Creates a shader program, given a vertex shader, fragment shader, and a name.
 * @param[in] vertShaderPath Path to the vertex shader
 * @param[in] fragShaderPath Path to the fragment shader
 * @param[in] name Name of the shader program
 * @return The reference to the shader program created
 */
Shader& Shader::LoadShader(std::string const& vertShaderPath, std::string const& fragShaderPath, std::string const& name)
{
	mStringToShaderMap[name] = Shader{ vertShaderPath, fragShaderPath };
	return mStringToShaderMap[name];
}

/**
 * @brief Returns a pointer to a shader program by name.
 *        Returns nullptr if shader program not found.
 *
 * @param[in] shaderName Name of the shader program
 * @return The pointer to the shader program.
 */
Shader* Shader::GetShader(std::string const& shaderName)
{
	auto it{ mStringToShaderMap.find(shaderName) };
	if (it == std::end(mStringToShaderMap)) return nullptr;
	return &it->second;
}

/**
 * @brief Reads a shader file and converts it to std::string
 * @param[in] path Path of the shader file
 * @return The shader as std::string
 */
std::string Shader::ReadShaderFile(std::string const& path)
{
	std::ifstream ifs{ path };
	std::ostringstream oss;
	oss << ifs.rdbuf();
	ifs.close();
	return oss.str();
}
