/*************************************************************//**
 * @file   ComponentManager.cpp
 * @brief  Function definition of ComponentManager
 *
 * Key features:
 * Returns its singleton instance
 *
 * Usage:
 *
 * Dependencies:
 *
 * @author HONG Xian Xiang
 * @date   3rd October 2024
 * Copyright 2024, Digipen Institute of Technology
*****************************************************************/

#include "Managers/ComponentManager.hpp"
#include "Core/Components.hpp"
#include "Scripts/Zombie.hpp"

ComponentManager::ComponentManager() : mTypeToSignatureMap{} {}

/**
 * @brief Get the singleton instance
 */
ComponentManager& ComponentManager::GetInstance()
{
	static ComponentManager instance;
	return instance;
}

/**
 * @brief Register components
 */
void ComponentManager::Init()
{
	RegisterComponent<Transform>();
	RegisterComponent<Rigidbody2D>();
	RegisterComponent<SpriteRenderer>();
	RegisterComponent<Animator>();
	RegisterComponent<MonoBehaviour>();
}
