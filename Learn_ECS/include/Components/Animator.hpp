/*************************************************************//**
 * @file   Animator.hpp
 * @brief  Definition of component Animator that stores all the animation for a single entity.
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

#ifndef ANIMATOR_HPP
#define ANIMATOR_HPP

#include <unordered_map>
#include <string>

#include "Interfaces/IComponent.hpp"

struct Frame
{
	int row{ 0 }, col{ 0 };
	float duration{ 1.f / 20.f };
};

struct Animation
{
	private:
		std::vector<Frame> frames{};

	public:
		Frame& operator[](size_t index);

		/**
		 * @brief Adds a frame to the end of the animation.
		 * @param[in] row Row of the sprite. Default is 0.
		 * @param[in] col Column of the sprite. Default is 0.
		 * @param[in] duration Duration of the frame before moving on to the next.
		 */
		void AddFrame(int row = 0, int col = 0, float duration = 1.f / 20.f);

		size_t GetFrameCount() const;
};

struct Animator : IComponent
{
	public:
		std::string currentAnimation{};
		float currentFrameTime{ 0.f };
		int currentFrameIndex{ 0 };
		int loopCount{ 0 }; // Loops infinitely if 0
		int loopsCompleted{ 0 };
		bool isPlaying{ true };
		bool flipX{ false };
		bool flipY{ false };

	private:
		std::unordered_map<std::string, Animation> stringToAnimationMap;

	public:
		Animator() = default;

		/**
		 * @brief Plays the animation.
		 * @param[in] animationName Name of the animation to play.
		 * @param[in] loopCount How many times the animation will be looped. <= 0 means infinite loops.
		 * @param[in] flipX Flips the frame in the x-axis.
		 * @param[in] flipY Flips the frame in the y-axis.
		 */
		void Play(std::string const& animationName, int loopCount = 0, bool flipX = false, bool flipY = false);

		/**
		 * @brief Pauses an animation, keeping the state, such as current frame.
		 */
		void Pause();

		/**
		 * @brief Resumes an animation, restoring the state, such as current frame.
		 */
		void Unpause();

		/**
		 * @brief Stops an animation, resetting the state.
		 */
		void Stop();

		/**
		 * @brief Adds a new animation.
		 * @param[in] animationName Name of the animation.
		 */
		void AddAnimation(std::string const& animationName);

		/**
		 * @brief Gets a reference to an existing animation.
		 * If the animation doesn't exist, return a default one, which doesn't do anything.
		 * @param[in] animationName Name of the animation.
		 */
		Animation& GetAnimation(std::string const& animationName);
};

#endif // !ANIMATOR_HPP
