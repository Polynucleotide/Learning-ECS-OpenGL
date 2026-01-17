/*************************************************************//**
 * @file   PhysicsSystem.hpp
 * @brief  Updates the objects' properties based on their physical properties
 * such as velocity.
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

#ifndef PHYSICS_SYSTEM_HPP
#define PHYSICS_SYSTEM_HPP

class PhysicsSystem
{
	public:
		static PhysicsSystem& GetInstance()
		{
			static PhysicsSystem instance;
			return instance;
		}

		PhysicsSystem(PhysicsSystem const&) = delete;
		PhysicsSystem& operator=(PhysicsSystem const&) = delete;

		void Init();

		/**
		 * @brief Updates the physical properties of objects like position, velocity, and rotation.
		 */
		void Update();

	private:
		PhysicsSystem() = default;
};

#endif // !PHYSICS_SYSTEM_HPP
