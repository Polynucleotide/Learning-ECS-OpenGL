/*************************************************************//**
 * @file   IComponent.ipp
 * @brief  Just the implementation of the GetComponent function in a component.
 *
 * Key features:
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

#include "Managers/EntityManager.hpp"
#include "Interfaces/IComponent.hpp"

/**
 * @brief Gets a component of an entity;
 * @param[in,out] handle Handle to the component.
 * @return Pointer to the component.
 */
template <typename T>
T* IComponent::GetComponent(T** handle)
{
	EntityManager& em{ EntityManager::GetInstance() };
	return em.GetComponent(em.GetEntity(entityId), handle);
}
