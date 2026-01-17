/*************************************************************//**
 * @file   ArchetypeManager.cpp
 * @brief  Function definition of ArchetypeManager
 *
 * Key features:
 * Returns its singleton instance
 * Create Archetypes
 * Destroy Archetypes
 * Get Archetypes
 * Add Entities to Archetypes
 * Remove Entities from Archetypes
 * Copy components from Archetype to Archetype
 *
 * Usage:
 *
 * Dependencies:
 *
 * @author HONG Xian Xiang
 * @date   3rd October 2024
 * Copyright 2024, Digipen Institute of Technology
*****************************************************************/

#include <Managers/ArchetypeManager.hpp>
#include <iostream>

ArchetypeManager::ArchetypeManager() :
	mSignatureToArchetypeMap{}
{}

/**
 * @brief Get the singleton instance
 */
ArchetypeManager& ArchetypeManager::GetInstance()
{
	static ArchetypeManager instance;
	return instance;
}

/**
 * @brief Creates an archetype with a given signature. Doesn't do anything if archetype exists
 * @param signature Signature of the Archetype to create
 * @return Pointer to the created archetype, or nullptr.
 */
Archetype* ArchetypeManager::CreateArchetype(Signature signature)
{
	mSignatureToArchetypeMap.insert({ signature, Archetype{ signature } });
	auto it{ mSignatureToArchetypeMap.find(signature) };
	if (it == std::end(mSignatureToArchetypeMap)) return nullptr;
	return &it->second;
}

/**
 * @brief Destroy an archetype
 * @param signature Signature of the Archetype
 */
void ArchetypeManager::DestroyArchetype(Signature signature)
{
	mSignatureToArchetypeMap.erase(signature);
}

/**
 * @brief Get a shared pointer to desired archetype.
 * @param signature Signature of the Archetype to get
 * @return Pointer to the created archetype, or nullptr.
 */
Archetype* ArchetypeManager::GetArchetype(Signature signature)
{
	auto it{ mSignatureToArchetypeMap.find(signature) };
	if (it == std::end(mSignatureToArchetypeMap))
		return nullptr;
	return &it->second;
}

/**
 * @brief Remove entity from archetype
 * @param[in] entity Readonly reference to entity
 */
void ArchetypeManager::RemoveEntity(Entity const& entity)
{
	mSignatureToArchetypeMap[entity.GetSignature()].RemoveEntity(entity.GetId());
}
