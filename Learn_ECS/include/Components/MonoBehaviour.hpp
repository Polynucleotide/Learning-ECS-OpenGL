/*************************************************************//**
 * @file   MonoBehaviour.hpp
 * @brief  Definition of the MonoBehaviour component. Abstract class
 *
 * Key features:
 * Gives users flexibility for their game logic.
 *
 * Usage:
 *
 * Dependencies:
 *
 * @author HONG Xian Xiang
 * @date   8th November 2024
 * Copyright 2024, Digipen Institute of Technology
*****************************************************************/

#ifndef MONO_BEHAVIOUR_HPP
#define MONO_BEHAVIOUR_HPP

#include "Interfaces/IComponent.hpp"

struct MonoBehaviour : IComponent
{
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual ~MonoBehaviour() = default;
};

#endif // !MONO_BEHAVIOUR_HPP
