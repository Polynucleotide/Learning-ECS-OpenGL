/*************************************************************//**
 * @file   MonoBehaviourSystem.hpp
 * @brief  Definition of MonoBehaviourSystem.
 * This system is calling the Start() and Update() function of all MonoBehaviours.
 *
 * Key features:
 * Init() calls the Start() function of all MonoBehvaiours.
 * Update() calls the Update() function of all MonoBehvaiours.
 *
 * Usage:
 *
 * Dependencies:
 *
 * @author HONG Xian Xiang
 * @date   8th November 2024
 * Copyright 2024, Digipen Institute of Technology
*****************************************************************/

#ifndef MONO_BEHAVIOUR_SYSTEM_HPP
#define MONO_BEHAVIOUR_SYSTEM_HPP

#include "Interfaces/ISystem.hpp"

class MonoBehaviourSystem : public ISystem
{
	/**
	 * @brief Simply calls Start() of all MonoBehaviours
	 */
	void Init() override;

	/**
	 * @brief Simply calls Update() of all MonoBehaviours
	 */
	void Update() override;
};

#endif // !MONO_BEHAVIOUR_SYSTEM_HPP
