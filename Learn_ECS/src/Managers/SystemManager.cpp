/*************************************************************//**
 * @file   SystemManager.cpp
 * @brief  Function definition in SystemManager
 *
 * Key features:
 * Adds a system
 * Initialize vector of systems
 * Update vector of systems
 *
 * Usage:
 * For each system, use AddSystem();
 * By calling InitSystems and UpdateSystems, all systems will be updated
 *
 * Dependencies:
 *
 * @author HONG Xian Xiang
 * @date   3rd October 2024
 * Copyright 2024, Digipen Institute of Technology
*****************************************************************/

#include <cassert>
#include "Managers/SystemManager.hpp"

std::vector<std::shared_ptr<ISystem>> SystemManager::systems;
std::unordered_map<std::string, std::shared_ptr<ISystem>> SystemManager::stringToSystemMap;

/**
 * @brief Adds a system of base type ISystem
 * @param[in] system Shared pointer to ISystem
 * @param[in] systemName Name of the system
 */
void SystemManager::AddSystem(std::shared_ptr<ISystem> const& system, std::string const& systemName)
{
	SystemManager::systems.push_back(system);
	stringToSystemMap[systemName] = system;
}

/**
 * @brief Initialize all system in the systems static member.
 * Is called once, before the game loop.
 */
void SystemManager::InitSystems()
{
	for (auto& pSystem : systems)
		pSystem->Init();
}

/**
 * @brief Updates all system in the systems static member.
 * Is called every frame.
 */
void SystemManager::UpdateSystems()
{
	for (auto& pSystem : systems)
		pSystem->Update();
}

/**
 * @brief Gets a system by name
 * @param[in] systemName Name of the system
 * @return Reference of a shared pointer to the system
 */
std::shared_ptr<ISystem>& SystemManager::GetSystem(std::string const& systemName)
{
	auto it{ stringToSystemMap.find(systemName) };
	assert(it != std::end(stringToSystemMap) && "System not found.");
	return it->second;
}
