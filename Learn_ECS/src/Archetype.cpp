/*************************************************************//**
 * @file   Archetype.cpp
 * @brief  Function definition in Archetype class
 *
 * Key features:
 * Construct an archetype with a particular signature. Each signature will be assigned a vector of component
 * Get archetype signature
 * Get the number of entities that belongs in this archetype
 * Add entity to archetype
 * Remove entity from archetype
 * Copy component data from archetype to another archetype
 * Print out the archetype
 *
 * Usage:
 * std::cout << archetype; to view the archetype's component vector
 *
 * Dependencies:
 *
 * @author HONG Xian Xiang
 * @date   3rd October 2024
 * Copyright 2024, Digipen Institute of Technology
*****************************************************************/

#include <Archetype.hpp>
#include <Entity.hpp>
#include <iostream>
#include "Managers/ArchetypeManager.hpp"
#include "Managers/HandleManager.hpp"

/**
 * @brief Constructor. Creates a component vector for each component type
 */
Archetype::Archetype(Signature signature) :
	mSignature{ signature }, mSignatureToComponentArrMap{},
	mEntityIdToIndexMap{}, mIndexToEntityIdMap{}
{
	Signature mask{1};
	for (size_t i{}; i < MAX_COMPONENTS; ++i)
	{
		if ((signature & mask) == mask)
			mSignatureToComponentArrMap.insert({ mask, ComponentArray{} });
		mask <<= 1;
	}
}

/**
 * @brief Get the signature of the archetype
 * @return Signature of the archetype
 */
Signature Archetype::GetSignature() const
{
	return mSignature;
}

/**
 * @brief Get the number of entities that belong in this archetype
 * @return Number of entities
 */
size_t Archetype::GetEntityCount() const
{
	return mEntityIdToIndexMap.size();
}

/**
 * @brief Adds an entity to Archetype
 * @param entityId Entity member id
 */
void Archetype::AddEntity(EntityId entityId)
{
	size_t index{ mEntityIdToIndexMap.size() };
	mEntityIdToIndexMap[entityId] = index;
	mIndexToEntityIdMap[index] = entityId;
	for (auto& pair : mSignatureToComponentArrMap)
		pair.second.resize(index + 1);
}

/**
 * @brief Removes an entity from Archetype
 * @param entityId Entity member id
 */
void Archetype::RemoveEntity(EntityId entityId)
{
	size_t entityCount{ mEntityIdToIndexMap.size() };

	// If removing the last entity, just destroy the Archetype.
	if (entityCount - 1 <= 0)
	{
		ArchetypeManager::GetInstance().DestroyArchetype(mSignature);
		return;
	}

	auto removedIndexIt{ mEntityIdToIndexMap.find(entityId) };
	if (removedIndexIt == std::end(mEntityIdToIndexMap))
	{
		std::cout << __FUNCTION__ << "() Entity not found in Archetype.\n";
		return;
	}

	size_t lastIndex{ entityCount - 1 };
	auto lastEntityIdIt{ mIndexToEntityIdMap.find(lastIndex) };
	if (lastEntityIdIt == std::end(mIndexToEntityIdMap))
	{
		std::cout << __FUNCTION__ << "() Last entity not found in Archetype.\n";
		return;
	}

	size_t removedIndex{ removedIndexIt->second };
	EntityId lastEntityId{ lastEntityIdIt->second };

	mEntityIdToIndexMap[lastEntityId] = removedIndex;
	mIndexToEntityIdMap[removedIndex] = lastEntityId;

	mEntityIdToIndexMap.erase(entityId);
	mIndexToEntityIdMap.erase(lastIndex);

	// Actually removing the entity components
	for (auto& pair : mSignatureToComponentArrMap)
	{
		pair.second[removedIndex] = std::move(pair.second[lastIndex]);
		pair.second.pop_back();
	}
}

/**
 * @brief Copy component data from an archetype to another
 * @param entityId Entity member id
 * @param to Pointer to the archetype
 */
void Archetype::MoveComponents(EntityId entityId, Archetype* to)
{
	// Entity must exist in both Archetypes first so that we can copy
	auto fromIndexIt{ mEntityIdToIndexMap.find(entityId) };
	if (fromIndexIt == std::end(mEntityIdToIndexMap))
	{
		std::cout << "Entity doesn't exist in \"From\" archetype.\n";
		return;
	}

	auto toIndexIt{ to->mEntityIdToIndexMap.find(entityId) };
	if (toIndexIt == std::end(to->mEntityIdToIndexMap))
	{
		std::cout << "Entity doesn't exist in \"To\" archetype.\n";
		return;
	}

	// Looping "From" Archetype
	for (auto& pair : mSignatureToComponentArrMap)
	{
		// Skip if "to" archetype doesn't have a particular component array.
		auto componentIt{ to->mSignatureToComponentArrMap.find(pair.first) };
		if (componentIt == std::end(to->mSignatureToComponentArrMap)) continue;
		componentIt->second[toIndexIt->second] = std::move(pair.second[fromIndexIt->second]);
	}
}

ComponentArray& Archetype::GetComponentArray(Signature componentSignature)
{
	return mSignatureToComponentArrMap[componentSignature];
}

size_t Archetype::GetIndexFromEntityId(EntityId entityId)
{
	auto it{ mEntityIdToIndexMap.find(entityId) };
	if (it == std::end(mEntityIdToIndexMap)) return static_cast<size_t>(-1);
	return it->second;
}

/**
 * @brief Displays the component vectors
 */
void Archetype::PrintArchetype() const
{
	std::cout << "\n[ Archetype " << mSignature << " ]\n";
	int count{0};
	for (auto const& pair : mSignatureToComponentArrMap)
	{
		for (size_t i{}; i < pair.second.size(); ++i)
		{
			std::cout << " _";
		}
		std::cout << "\n|";
		for (size_t i{}; i < pair.second.size(); ++i)
		{
			std::cout << "_|";
		}
		std::cout << " Component " << ++count << "\n";
	}
	std::cout << '\n';
}

std::ostream& operator<<(std::ostream& os, Archetype const& archetype)
{
	archetype.PrintArchetype();
	return os;
}
