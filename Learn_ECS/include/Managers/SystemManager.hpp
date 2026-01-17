/*************************************************************//**
 * @file   SystemManager.hpp
 * @brief  Manager of all systems
 *
 * Key features:
 * Add a system to a vector of system
 * Initialize all systems in the vector
 * Update all systems in the vector
 *
 * Usage:
 *
 * Dependencies:
 *
 * @author HONG Xian Xiang
 * @date   3rd October 2024
 * Copyright 2024, Digipen Institute of Technology
*****************************************************************/

#ifndef SYSTEM_MANAGER_HPP
#define SYSTEM_MANAGER_HPP

#include <unordered_map>
#include <vector>
#include <memory>
#include <string>
#include "Interfaces/ISystem.hpp"

class SystemManager
{
	public:
		/**
		 * @brief Adds a system of base type ISystem
		 * @param[in] system Shared pointer to ISystem
		 * @param[in] systemName Name of the system
		 */
		static void AddSystem(std::shared_ptr<ISystem> const& system, std::string const& systemName);

		/**
		 * @brief Initialize all system in the systems static member.
		 * Is called once, before the game loop.
		 */
		static void InitSystems();

		/**
		 * @brief Updates all system in the systems static member.
		 * Is called every frame.
		 */
		static void UpdateSystems();

		/**
		 * @brief Gets a system by name
		 * @param[in] systemName Name of the system
		 * @return Reference of a shared pointer to the system
		 */
		static std::shared_ptr<ISystem>& GetSystem(std::string const& systemName);

	private:
		static std::vector<std::shared_ptr<ISystem>> systems;
		static std::unordered_map<std::string, std::shared_ptr<ISystem>> stringToSystemMap;
};

#endif // !SYSTEM_MANAGER_HPP
