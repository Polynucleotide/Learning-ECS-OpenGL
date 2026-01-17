/*************************************************************//**
 * @file   Transform.hpp
 * @brief  Component of type Transform of an entity
 *
 * Key features:
 * Position (x, y)
 * Rotation (a)
 * Width    (w)
 * Height   (h)
 *
 * Usage:
 *
 * Dependencies:
 *
 * @author HONG Xian Xiang
 * @date   3rd October 2024
 * Copyright 2024, Digipen Institute of Technology
*****************************************************************/

#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "Interfaces/IComponent.hpp"

struct Transform : IComponent
{
	float x, y, a, w, h;
	Transform(float _x, float _y, float _a, float _w, float _h);
};

#endif // !TRANSFORM_HPP
