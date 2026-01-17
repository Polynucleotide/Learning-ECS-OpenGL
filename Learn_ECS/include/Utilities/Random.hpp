/*************************************************************//**
 * @file   Random.hpp
 * @brief  Function declaration to generate random things
 *
 * Key features:
 * Random float
 *
 * Usage:
 * Random::RandomFloat(-1.f, 1.f) yields [-1, 1]
 *
 * Dependencies:
 *
 * @author HONG Xian Xiang
 * @date   3rd October 2024
 * Copyright 2024, Digipen Institute of Technology
*****************************************************************/

#ifndef RANDOM_HPP
#define RANDOM_HPP

namespace Random
{
	/**
	 * @brief Generates a random float, inclusive.
	 * @param[in] min Minimum value
	 * @param[in] max Maximum value
	 */
	float RandomFloat(float min, float max);

	/**
	 * @brief Generates a random int, inclusive.
	 * @param[in] min Minimum value
	 * @param[in] max Maximum value
	 */
	int RandomInt(int min, int max);
}

#endif // !RANDOM_HPP
