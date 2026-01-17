/*************************************************************//**
 * @file   GraphicSystem.hpp
 * @brief  Draw objects to the screen
 *
 * Key features:
 * Draw objects to the screen.
 * Stores the maximum batch size
 * Stores a vector of matrix 3x3
 * Maps uniform names to their location,
 * so we don't have to keep doing uniform lookups
 * Initialize shader and VAO
 *
 * Usage:
 *
 * Dependencies:
 *
 * @author HONG Xian Xiang
 * @date   3rd October 2024
 * Copyright 2024, Digipen Institute of Technology
*****************************************************************/

#ifndef GRAPHIC_SYSTEM_HPP
#define GRAPHIC_SYSTEM_HPP

#include <iostream>
#include <unordered_map>
#include <string>
#include <glm/glm.hpp>
#include "Interfaces/ISystem.hpp"

class GraphicSystem
{
	public:
		/**
		 * @brief Initialize batch size. Create shader program and VAO
		 */
		static GraphicSystem& GetInstance()
		{
			static GraphicSystem instance;
			return instance;
		}

		GraphicSystem(GraphicSystem const&) = delete;
		GraphicSystem& operator=(GraphicSystem const&) = delete;

		/**
		 * @brief Initialize batch size. Create shader program and VAO
		 */
		void Init();

		void Update();

		/**
		 * @brief Renders objects to the screen.
		 */
		void Draw();

		/**
		 * @brief Frees memory allocated for shader program and VAOs.
		 */
		void Free();

	private:
		GraphicSystem() = default;
};

#endif // !GRAPHIC_SYSTEM_HPP
