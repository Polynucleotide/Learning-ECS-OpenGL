/*************************************************************//**
 * @file   EntityManager.cpp
 * @brief  Function definition of EntityManager
 *
 * Key features:
 * Returns its singleton instance
 * Create an entity
 * Get the number of existing entities
 *
 * Usage:
 *
 * Dependencies:
 *
 * @author HONG Xian Xiang
 * @date   3rd October 2024
 * Copyright 2024, Digipen Institute of Technology
*****************************************************************/
#include <cassert>
#include "Managers/EntityManager.hpp"
#include "Managers/HandleManager.hpp"

EntityManager::EntityManager() : mIdCounter{0}
{
	mEntities.reserve(MAX_ENTITIES);
}

/**
 * @brief Get the singleton instance
 */
EntityManager& EntityManager::GetInstance()
{
	static EntityManager instance;
	return instance;
}

/**
 * @brief Create an entity.
 * @return A reference to the entity.
 */
Entity& EntityManager::CreateEntity()
{
	EntityId id{ mIdCounter++ };
	size_t index{ mEntities.size() };
	mEntities.push_back(Entity{ id });
	mEntityIdToIndexMap[id] = index;
	mIndexToEntityIdMap[index] = id;
	return mEntities[index];
}

/**
 * @brief Get an entity from it's ID.
 * @param[in] entityId ID of the entity
 * @return A reference to the entity.
 */
Entity& EntityManager::GetEntity(EntityId entityId)
{
	auto indexIt{ mEntityIdToIndexMap.find(entityId) };
	assert(indexIt != std::end(mEntityIdToIndexMap) && "Entity ID not found.");
	return mEntities[indexIt->second];
}

/**
 * @brief Destroy an entity.
 * @paran[in] entity Reference to an entity
 */
void EntityManager::DestroyEntity(Entity const& entity)
{
	EntityId entityId{ entity.GetId() };

	auto removedIndexIt{ mEntityIdToIndexMap.find(entityId) };
	if (removedIndexIt == std::end(mEntityIdToIndexMap)) return;

	// Remove from archetype
	// TODO Maybe decouple
	HandleManager& hm{ HandleManager::GetInstance() };
	hm.DestroyEntityHandles(entity);
	ArchetypeManager::GetInstance().RemoveEntity(entity);

	size_t removedIndex{ removedIndexIt->second };
	size_t lastIndex{ mEntities.size() - 1 };
	EntityId lastEntityId{ mIndexToEntityIdMap[lastIndex] };

	mEntityIdToIndexMap[lastEntityId] = removedIndex;
	mIndexToEntityIdMap[removedIndex] = lastEntityId;

	mEntityIdToIndexMap.erase(entityId);
	mIndexToEntityIdMap.erase(lastIndex);

	mEntities[removedIndex] = std::move(mEntities[lastIndex]);
	mEntities.pop_back();

	if (mEntities.size() > 0)
		hm.UpdateEntityHandles(mEntities[removedIndex]);
}

/**
 * @brief Get the number of existing entities
 * @return The number of entities
 */
size_t EntityManager::GetEntityCount() const
{
	return mEntities.size();
}
