/*************************************************************//**
 * @file   Shader.hpp
 * @brief  Contains definition of a shader program and function declarations for the shader program
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

#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>
#include <unordered_map>
#include <string>

class Shader
{
	public:
		Shader() = default;

		/**
		 * @brief Ctor to create a shader program
		 * @param[in] vertShaderPath Path to the vertex shader
		 * @param[in] fragShaderPath Path to the fragment shader
		 */
		Shader(std::string const& vertShaderPath, std::string const& fragShaderPath);

		/**
		 * @brief Returns the shader program's handle
		 * @return The shader program's handle
		 */
		GLint GetId() const;

		/**
		 * @brief Add a uniform and its location to a map to reduce look up time
		 * @param[in] uniformName Name of the uniform
		 */
		void AddUniform(std::string const& uniformName);

		/**
		 * @brief Set a uniform for a 3x3 matrix
		 * @param[in] uniformName Name of the uniform
		 * @param[in] value Value of the uniform in the shader
		 */
		void SetUniform(std::string const& uniformName, GLfloat const* value);

		/**
		 * @brief Set a uniform for an array of ints
		 * @param[in] uniformName Name of the uniform
		 * @param[in] count Number of ints
		 * @param[in] value Pointer to the array of ints
		 */
		void SetUniform(std::string const& uniformName, GLsizei count, GLint const* value);

		/**
		 * @brief Reads a shader file and converts it to std::string
		 * @param[in] path Path of the shader file
		 * @return The shader as std::string
		 */
		static std::string ReadShaderFile(std::string const& path);

		/**
		 * @brief Creates a shader program, given a vertex shader, fragment shader, and a name.
		 * @param[in] vertShaderPath Path to the vertex shader
		 * @param[in] fragShaderPath Path to the fragment shader
		 * @param[in] name Name of the shader program
		 * @return The reference to the shader program created
		 */
		static Shader& LoadShader(std::string const& vertShaderPath, std::string const& fragShaderPath, std::string const& name);

		/**
		 * @brief Returns a pointer to a shader program by name.
		 *        Returns nullptr if shader program not found.
		 *
		 * @param[in] shaderName Name of the shader program
		 * @return The pointer to the shader program.
		 */
		static Shader* GetShader(std::string const& shaderName);

	private:
		GLuint mId{ 0 };
		std::unordered_map<std::string, GLint> mUniformToLocationMap{};
		static std::unordered_map<std::string, Shader> mStringToShaderMap;
};

#endif // !SHADER_HPP
