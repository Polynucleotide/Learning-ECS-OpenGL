/*************************************************************//**
 * @file   Random.cpp
 * @brief  Function definition to generate random things
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

#include <Utilities/Random.hpp>
#include <cstdlib>

// TODO Use the C++ random instead of C
namespace Random
{
	/**
	 * @brief Generates a random float, inclusive.
	 * @param[in] min Minimum value
	 * @param[in] max Maximum value
	 */
	float RandomFloat(float min, float max)
	{
		float x{ static_cast<float>(rand()) / static_cast<float>(RAND_MAX) };
		float m{ max - min };
		return m * x + min;
	}

	/**
	 * @brief Generates a random int, inclusive.
	 * @param[in] min Minimum value
	 * @param[in] max Maximum value
	 */
	int RandomInt(int min, int max)
	{
		return rand() % (max - min + 1) + min;
	}
}