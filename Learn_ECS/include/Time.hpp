/*************************************************************//**
 * @file   Time.hpp
 * @brief  Keep tracks of the time between each from in seconds
 *
 * Key features:
 *
 * Usage:
 * Time::deltaTime to get the delta time.
 *
 * Dependencies:
 * glfw3
 *
 * @author HONG Xian Xiang
 * @date   3rd October 2024
 * Copyright 2024, Digipen Institute of Technology
*****************************************************************/

#ifndef TIME_HPP
#define TIME_HPP

#include <GLFW/glfw3.h>

class Time
{
	private:
		static double oldTime;

	public:
		static double deltaTime;
		
		/**
		 * @brief Calculates deltaTime
		 */
		static void Update();
};

#endif // !TIME_HPP
