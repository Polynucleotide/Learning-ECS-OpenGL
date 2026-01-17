/*************************************************************//**
 * @file   Zombie.cpp
 * @brief  Start and Update function definition for Zombie which inherits from MonoBehaviour.
 * This is just a test MonoBehvaiour. Problem is identifying this in at run-time.
 *
 * Key features:
 *
 * Usage:
 *
 * Dependencies:
 *
 * @author HONG Xian Xiang
 * @date   8th November 2024
 * Copyright 2024, Digipen Institute of Technology
*****************************************************************/

#include "Scripts/Zombie.hpp"
#include "Systems/InputSystem.hpp"
#include "Core/Components.hpp"
#include "Time.hpp"

Transform* transform = nullptr;
Animator* animator = nullptr;

void Zombie::Start()
{
	transform = GetComponent<Transform>(&transform);
	animator = GetComponent<Animator>(&animator);
}

void Zombie::Update()
{
	float velocity{ 500.f * static_cast<float>(Time::deltaTime) };
	if (InputSystem::KeyDown(InputSystem::W)) transform->y += velocity;
	if (InputSystem::KeyDown(InputSystem::S)) transform->y -= velocity;
	if (InputSystem::KeyDown(InputSystem::A))
	{
		animator->flipX = true;
		transform->x -= velocity;
	}
	if (InputSystem::KeyDown(InputSystem::D))
	{
		animator->flipX = false;
		transform->x += velocity;
	}
}
