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

#include <Time.hpp>

double Time::oldTime{ 0. };
double Time::deltaTime{ 0. };

/**
 * @brief Calculates deltaTime
 */
void Time::Update()
{
	double newTime = glfwGetTime();
	deltaTime = newTime - oldTime;
	oldTime = newTime;
}
