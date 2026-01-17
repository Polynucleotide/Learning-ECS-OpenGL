/*************************************************************//**
 * @file   PhysicsSystem.cpp
 * @brief  Function definitions of PhysicsSystem.
 *
 * Key features:
 * Initialize the physics system.
 * Update the physics system (Updates entities' position and rotation).
 *
 * Usage:
 * Called by SystemManager where it loops through all registered
 * systems and calls their Update() function
 *
 * Dependencies:
 *
 * @author HONG Xian Xiang
 * @date   3rd October 2024
 * Copyright 2024, Digipen Institute of Technology
*****************************************************************/

#include <iostream>
#include "Components/Transform.hpp"
#include "Components/Rigidbody2D.hpp"
#include "Systems/PhysicsSystem.hpp"
#include "Managers/ArchetypeManager.hpp"
#include "Time.hpp"

void PhysicsSystem::Init()
{
	std::cout << __FUNCTION__ << '\n';
}

/**
 * @brief Updates the physical properties of objects like position, velocity, and rotation.
 */
void PhysicsSystem::Update()
{
#if 1
	ArchetypeManager& am{ ArchetypeManager::GetInstance() };
	ArchetypeSet set{ am.GetArchetypeSet<Transform, Rigidbody2D>() };
	for (auto& arch : set)
	{
		auto& tv{ arch->GetComponentArray<Transform>() };
		auto& rv{ arch->GetComponentArray<Rigidbody2D>() };
		for (size_t i{}; i < arch->GetEntityCount(); ++i)
		{
			Transform& transform{ std::any_cast<Transform&>(tv[i]) };
			Rigidbody2D const& rb{ std::any_cast<Rigidbody2D&>(rv[i]) };
			transform.y -= rb.vy * static_cast<float>(Time::deltaTime);
			transform.a += 3.1415f / 4.f * static_cast<float>(Time::deltaTime);
		}
	}
#endif
}
