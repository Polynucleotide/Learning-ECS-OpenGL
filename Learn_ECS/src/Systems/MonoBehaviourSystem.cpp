/*************************************************************//**
 * @file   MonoBehaviourSystem.cpp
 * @brief  Function definitions of MonoBehaviourSystem.
 * This system is calling the Start() and Update() function of all MonoBehaviours.
 *
 * Key features:
 * Init() calls the Start() function of all MonoBehvaiours.
 * Update() calls the Update() function of all MonoBehvaiours.
 *
 * Usage:
 *
 * Dependencies:
 *
 * @author HONG Xian Xiang
 * @date   8th November 2024
 * Copyright 2024, Digipen Institute of Technology
*****************************************************************/

#include "Systems/MonoBehaviourSystem.hpp"
#include "Managers/ArchetypeManager.hpp"

/**
 * @brief Simply calls Start() of all MonoBehaviours
 */
void MonoBehaviourSystem::Init()
{
	// Oh my god it works
	ArchetypeManager& am{ ArchetypeManager::GetInstance() };
	ArchetypeSet set{ am.GetArchetypeSet<MonoBehaviour>() };
	for (auto& arch : set)
	{
		auto& mbv{ arch->GetComponentArray<MonoBehaviour>() };
		for (size_t i{}; i < arch->GetEntityCount(); ++i)
		{
			MonoBehaviour* mb{ reinterpret_cast<MonoBehaviour*>(&mbv[i]) };
			mb->Start();
		}
	}
}

/**
 * @brief Simply calls Update() of all MonoBehaviours
 */
void MonoBehaviourSystem::Update()
{
	// Oh my god it works
	ArchetypeManager& am{ ArchetypeManager::GetInstance() };
	ArchetypeSet set{ am.GetArchetypeSet<MonoBehaviour>() };
	for (auto& arch : set)
	{
		auto& mbv{ arch->GetComponentArray<MonoBehaviour>() };
		for (size_t i{}; i < arch->GetEntityCount(); ++i)
		{
			MonoBehaviour* mb{ reinterpret_cast<MonoBehaviour*>(&mbv[i]) };
			mb->Update();
		}
	}
}
