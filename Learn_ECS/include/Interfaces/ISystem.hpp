/*************************************************************//**
 * @file   ISystem.hpp
 * @brief  Base class ISystem, acts as an interface
 *
 * Key features:
 *
 * Usage:
 *
 * Dependencies:
 *
 * @author HONG Xian Xiang
 * @date   3rd October 2024
 * Copyright 2024, Digipen Institute of Technology
*****************************************************************/

#ifndef I_SYSTEM_HPP
#define I_SYSTEM_HPP

class ISystem
{
	public:
		virtual void Init() = 0;
		virtual void Update() = 0;
		virtual ~ISystem() noexcept = default;
};

#endif // !I_SYSTEM_HPP
