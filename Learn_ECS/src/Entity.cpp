/*************************************************************//**
 * @file   Entity.hpp
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

#include "Entity.hpp"

/**
 * @brief Constructor
 * @param id Entity member id
 */
Entity::Entity(EntityId id) :
	mSignature{ 0 }, mId{ id }
{};

/**
 * @brief Get entity's archetype signature
 * @return The signature of entity's archetype
 */
Signature Entity::GetSignature() const
{
	return mSignature;
}

/**
 * @brief Set entity's archetype
 */
void Entity::SetSignature(Signature signature)
{
	mSignature = signature;
}

/**
 * @brief Get entity id
 * @return Entity member id
 */
EntityId Entity::GetId() const
{
	return mId;
}
