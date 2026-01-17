/*************************************************************//**
 * @file   Application.hpp
 * @brief  Application to store static variables like
 * window size and NDC matrix.
 *
 * Key features:
 *
 * Usage:
 * Application::WIDTH or Application::HEIGHT to get the window's dimensions
 *
 * Dependencies:
 *
 * @author HONG Xian Xiang
 * @date   3rd October 2024
 * Copyright 2024, Digipen Institute of Technology
*****************************************************************/

#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

class Application
{
	public:
		/**
		 * @brief Get the singleton instance
		 */
		static Application& GetInstance();

		/**
		 * @brief Delete copy constructor and copy assignment because singleton
		 */
		Application(Application const&) = delete;
		void operator=(Application const&) = delete;

		/**
		 * @brief Initialize engine
		 */
		static void Init();

		/**
		 * @brief Initialize OpenGL
		 */
		static void InitOpenGL();

		/**
		 * @brief Starts the game loop
		 */
		static void Run();

		/**
		 * @brief Updates world to NDC matrix
		 */
		static void Update();

		/**
		 * @brief Free allocated memory
		 */
		static void Exit();

		static GLFWwindow* GetWindow();
		static glm::mat3 const& GetWorldToNDCMatrix();
		static GLint GetMaxTextureUnits();

		static const int WIDTH{ 1920 };
		static const int HEIGHT{ 1080 };

	private:
		Application() = default;
		~Application() = default;

		static GLFWwindow* ptrWindow;
		static glm::mat3 worldToNDCMatrix;
		static GLint maxTextureUnits;
		
		// VAOs
		std::vector<GLuint> mModels;
};

#endif // !APPLICATION_HPP

