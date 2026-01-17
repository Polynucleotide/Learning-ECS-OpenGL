/*************************************************************//**
 * @file   Zombie.hpp
 * @brief  Definition of Zombie which inherits from MonoBehaviour.
 * This is just a test MonoBehvaiour. Problem is identifying this in at run-time.
 *
 * Key features:
 *
 * Usage:
 *
 * Dependencies:
 *
 * @author HONG Xian Xiang
 * @date   8th November 2024
 * Copyright 2024, Digipen Institute of Technology
*****************************************************************/

#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include "Components/MonoBehaviour.hpp"

class Zombie : public MonoBehaviour
{
	void Start() override;
	void Update() override;
};

#endif // !ZOMBIE_HPP
