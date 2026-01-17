/*************************************************************//**
 * @file   Entity.cpp
 * @brief  Represents a game object (not really).
 *
 * Key features:
 *
 * Usage:
 * Lightweight object that can map to component data
 *
 * Dependencies:
 *
 * @author HONG Xian Xiang
 * @date   3rd October 2024
 * Copyright 2024, Digipen Institute of Technology
*****************************************************************/

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "Alias.hpp"

class Entity
{
	public:
		/**
		 * @brief Constructor
		 * @param id Entity member id
		 */
		Entity(EntityId id);

		/**
		 * @brief Get entity's archetype signature
		 * @return The signature of entity's archetype
		 */
		Signature GetSignature() const;

		/**
		 * @brief Set entity's archetype
		 */
		void SetSignature(Signature signature);

		/**
		 * @brief Get entity id
		 * @return Entity member id
		 */
		EntityId GetId() const;

	private:
		Signature mSignature; // Archetype it belongs to
		EntityId mId;
};

#endif // !ENTITY_HPP
