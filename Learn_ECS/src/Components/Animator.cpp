/*************************************************************//**
 * @file   Animator.cpp
 * @brief  Function definitions of component Animator that stores all the animation for a single entity.
 *
 * Key features:
 * A Frame struct, which contains the sprite sheet's row, column, and duration.
 *
 * An Animation struct, which contains a vector of Frames. The vector is iterated through
 * for an animation to play.
 *
 * The Animator component. Contains information of the current animation it is playing, and also
 * stores all the animation created for a single entity.
 *
 * Usage:
 * 1. Create the animation.                     animator->AddAnimation("Walk");
 * 2. Get the animation's reference.            Animation& animation{ animator->GetAnimation("Walk") };
 * 3. Add frames to the animation reference.    animation.AddFrame(1, 0);
 * 4. Repeat step 3 however many times.
 * 5. Call "Play" with the desired animation.   animator->Play("Walk");
 *
 * Dependencies:
 *
 * @author HONG Xian Xiang
 * @date   8th November 2024
 * Copyright 2024, Digipen Institute of Technology
*****************************************************************/

#include <cassert>
#include "Components/Animator.hpp"

/**
 * @brief Plays the animation.
 * @param[in] animationName Name of the animation to play.
 * @param[in] loopCount How many times the animation will be looped. <= 0 means infinite loops.
 * @param[in] flipX Flips the frame in the x-axis.
 * @param[in] flipY Flips the frame in the y-axis.
 */
void Animator::Play(std::string const& animationName, int _loopCount, bool _flipX, bool _flipY)
{
	currentAnimation = animationName;
	currentFrameTime = 0.f;
	currentFrameIndex = 0;
	loopCount = _loopCount;
	loopsCompleted = 0;
	isPlaying = true;
	flipX = _flipX;
	flipY = _flipY;
}

/**
 * @brief Pauses an animation, keeping the state, such as current frame.
 */
void Animator::Pause()
{
	isPlaying = false;
}

/**
 * @brief Resumes an animation, restoring the state, such as current frame.
 */
void Animator::Unpause()
{
	isPlaying = true;
}

/**
 * @brief Stops an animation, resetting the state.
 */
void Animator::Stop()
{
	currentFrameTime = 0.f;
	currentFrameIndex = 0;
	loopsCompleted = 0;
	isPlaying = false;
}

/**
 * @brief Adds a new animation.
 * @param[in] animationName Name of the animation.
 */
void Animator::AddAnimation(std::string const& animationName)
{
	stringToAnimationMap[animationName] = Animation{};
}

/**
 * @brief Gets a reference to an existing animation.
 * If the animation doesn't exist, return a default one.
 * @param[in] animationName Name of the animation.
 */
Animation& Animator::GetAnimation(std::string const& animationName)
{
	auto it{ stringToAnimationMap.find(animationName) };

	// If animation not found
	if (it == std::end(stringToAnimationMap))
		return stringToAnimationMap["default"];

	return it->second;
}

Frame& Animation::operator[](size_t index)
{
	return frames[index];
}

/**
 * @brief Adds a frame to the end of the animation.
 * @param[in] row Row of the sprite. Default is 0.
 * @param[in] col Column of the sprite. Default is 0.
 * @param[in] duration Duration of the frame before moving on to the next.
 */
void Animation::AddFrame(int row, int col, float duration)
{
	frames.push_back(Frame{ row, col, duration });
}

size_t Animation::GetFrameCount() const
{
	return frames.size();
}
