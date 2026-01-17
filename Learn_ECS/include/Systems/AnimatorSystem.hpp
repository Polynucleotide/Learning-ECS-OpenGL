/*************************************************************//**
 * @file   AnimatorSystem.hpp
 * @brief  Definition of AnimatorSystem. This system is responsible for
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

#ifndef ANIMATOR_SYSTEM_HPP
#define ANIMATOR_SYSTEM_HPP

#include "Interfaces/ISystem.hpp"

class AnimatorSystem : public ISystem
{
	void Init() override;

	/**
	 * @brief Loops through entities containing an Animator and SpriteRenderer component.
	 * Updates the SpriteRenderer's row and column, which decides which sprite to display.
	 * Will not update SpriteRenderer if Animator is paused or stopped.
	 */
	void Update() override;
};

#endif // !ANIMATOR_SYSTEM_HPP
