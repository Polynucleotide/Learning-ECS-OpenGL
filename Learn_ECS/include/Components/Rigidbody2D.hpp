/*************************************************************//**
 * @file   Rigidbody2D.hpp
 * @brief  Component of type Rigidbody2D of an entity
 *
 * Key features:
 * Contains velocity data
 *
 * Usage:
 *
 * Dependencies:
 *
 * @author HONG Xian Xiang
 * @date   3rd October 2024
 * Copyright 2024, Digipen Institute of Technology
*****************************************************************/

#ifndef RIGIDBODY_2D_HPP
#define RIGIDBODY_2D_HPP

#include "Interfaces/IComponent.hpp"

struct Rigidbody2D : IComponent
{
	float vx, vy; // TODO use 2D vector instead of floats
	Rigidbody2D(float _x, float _y);
};

#endif // !RIGIDBODY_2D_HPP
