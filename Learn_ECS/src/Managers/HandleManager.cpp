/*************************************************************//**
 * @file   HandleManager.cpp
 * @brief  Function definitions of component handles
 *
 * Key features:
 * Maintain the handles of components
 * T* t = GetComponent<T>();
 * Stops t from being a dangling pointer
 *
 * Usage:
 *
 * Dependencies:
 *
 * @author HONG Xian Xiang
 * @date   20th October 2024
 * Copyright 2024, Digipen Institute of Technology
*****************************************************************/

#include "Managers/HandleManager.hpp"
#include "Managers/ArchetypeManager.hpp"
#include "Archetype.hpp"

/**
 * @brief Add a handle
 * Whenever the component held by an entity shifts, update its pointer.
 * @param[in] entityId Entity ID
 * @param[in] componentSignature Signature of the specific component.
 * @param[in,out] handle Pointer to the pointer to the component. lol.
 */
void HandleManager::AddHandle(EntityId entityId, Signature componentSignature, void** handle)
{
	// Set old handle to nullptr
	void**& oldHandle{ mEntityIdToHandleMap[entityId][componentSignature] };
	if (oldHandle) *oldHandle = nullptr;

	// Set old handle with new handle
	oldHandle = handle;
}

/**
 * @brief Update component handle
 * @param[in] entity Readonly reference to entity
 */
void HandleManager::UpdateEntityHandles(Entity const& entity)
{
	EntityId entityId{ entity.GetId() };
	auto it{ mEntityIdToHandleMap.find(entityId) };
	if (it == std::end(mEntityIdToHandleMap)) return;

	Archetype* archetype{ ArchetypeManager::GetInstance().GetArchetype(entity.GetSignature()) };
	if (archetype == nullptr)
	{
		std::cout << __FUNCTION__ << "() Archetype not found.\n";
		return;
	}

	size_t index{ archetype->GetIndexFromEntityId(entityId) };
	if (index == static_cast<size_t>(-1))
	{
		std::cout << __FUNCTION__ << "() Entity not found.\n";
		return;
	}

	for (auto& signatureToHandle : it->second)
	{
		auto& componentArray{ archetype->GetComponentArray(signatureToHandle.first) };
		if (signatureToHandle.second)
			*signatureToHandle.second = &componentArray[index];
	}
}

/**
 * @brief Sets all handles to a detroyed entity to nullptr
 * @param[in] entity Readonly reference to entity
 */
void HandleManager::DestroyEntityHandles(Entity const& entity)
{
	auto& signatureToHandleMap{ mEntityIdToHandleMap[entity.GetId()] };
	for (auto& signatureToHandle : signatureToHandleMap)
		if (signatureToHandle.second) *signatureToHandle.second = nullptr;
	mEntityIdToHandleMap.erase(entity.GetId());
}
