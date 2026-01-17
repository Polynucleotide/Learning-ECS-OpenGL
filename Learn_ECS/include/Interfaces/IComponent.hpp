/*************************************************************//**
 * @file   IComponent.hpp
 * @brief  Base class IComponent. Allows us to call GetComponent inside a component.
 * Used in MonoBehaviours.
 *
 * Key features:
 * Stores the entity's ID to know which component to get.
 *
 * Usage:
 * Used in MonoBehaviours.
 *
 * Dependencies:
 *
 * @author HONG Xian Xiang
 * @date   8th November 2024
 * Copyright 2024, Digipen Institute of Technology
*****************************************************************/

#ifndef I_COMPONENT_HPP
#define I_COMPONENT_HPP

#include "Alias.hpp"

struct IComponent
{
	// Initialize to max value because compiler can't stop complaining
	EntityId entityId{ static_cast<EntityId>(-1) };

	/**
	 * @brief Gets a component of an entity;
	 * @param[in,out] handle Handle to the component.
	 * @return Pointer to the component.
	 */
	template <typename T>
	T* GetComponent(T** handle);

	virtual ~IComponent() noexcept = default;
};

#endif // !I_COMPONENT_HPP
