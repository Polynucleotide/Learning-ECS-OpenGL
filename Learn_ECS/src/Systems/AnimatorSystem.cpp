/*************************************************************//**
 * @file   AnimatorSystem.cpp
 * @brief  Function definitions of AnimatorSystem. This system is responsible for
 * updating frames of an entity's animation.
 *
 * Key features:
 * Iterate through frames of an animation once the fram duration is reached.
 * Able to limit a finite amount of times an animation plays. Can be infinite.
 *
 * Usage:
 *
 * Dependencies:
 *
 * @author HONG Xian Xiang
 * @date   8th November 2024
 * Copyright 2024, Digipen Institute of Technology
*****************************************************************/

#include <iostream>
#include "Core/Components.hpp"
#include "Systems/AnimatorSystem.hpp"
#include "Managers/ArchetypeManager.hpp"
#include "Time.hpp"

void AnimatorSystem::Init()
{
	std::cout << __FUNCTION__ << '\n';
}

/**
 * @brief Loops through entities containing an Animator and SpriteRenderer component.
 * Updates the SpriteRenderer's row and column, which decides which sprite to display.
 * Will not update SpriteRenderer if Animator is paused or stopped.
 */
void AnimatorSystem::Update()
{
	ArchetypeSet set{ ArchetypeManager::GetInstance().GetArchetypeSet<Animator, SpriteRenderer>() };
	for (auto& arch : set)
	{
		auto& srv = arch->GetComponentArray<SpriteRenderer>();
		auto& av = arch->GetComponentArray<Animator>();

		size_t entityCount{ arch->GetEntityCount() };
		for (size_t i{}; i < entityCount; ++i)
		{
			Animator& animator{ std::any_cast<Animator&>(av[i]) };
			if (!animator.isPlaying) continue;

			Animation& animation = animator.GetAnimation(animator.currentAnimation);
			size_t animFrameCount{ animation.GetFrameCount() };
			if (animFrameCount <= 0) continue;

			// Maximum loop count reached
			if (animator.loopCount > 0 && animator.loopsCompleted >= animator.loopCount)
			{
				animator.Stop();
				continue;
			}

			// Frame duration not reached
			Frame& frame = animation[animator.currentFrameIndex];
			if (animator.currentFrameTime < frame.duration)
			{
				animator.currentFrameTime += static_cast<float>(Time::deltaTime);
				continue;
			}

			// Go next frame
			SpriteRenderer& sr{ std::any_cast<SpriteRenderer&>(srv[i]) };
			sr.row = frame.row;
			sr.col = frame.col;
			sr.flipX = animator.flipX;
			sr.flipY = animator.flipY;

			int nextFrameIndex{ animator.currentFrameIndex + 1 };
			animator.currentFrameIndex = nextFrameIndex % animFrameCount;
			animator.currentFrameTime = 0.f;

			if (nextFrameIndex >= animFrameCount)
				++animator.loopsCompleted;
		}
	}
}
