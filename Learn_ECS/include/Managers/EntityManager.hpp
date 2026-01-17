/*************************************************************//**
 * @file   EntityManager.hpp
 * @brief  Manager of all entities
 *
 * Key features:
 * Is a Singleton
 * Create and Get entities
 * Get entity count
 * Add component to entity
 * Remove component from entity
 * Get component from entity
 *
 * Usage:
 * Use EntityManager to add, remove and get components
 *
 * Dependencies:
 *
 * @author HONG Xian Xiang
 * @date   3rd October 2024
 * Copyright 2024, Digipen Institute of Technology
*****************************************************************/

#ifndef	ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include <vector>
#include <unordered_map>
#include "Entity.hpp"

class EntityManager
{
	public:
		/**
		 * @brief Get the singleton instance
		 */
		static EntityManager& GetInstance();

		/**
		 * @brief Delete copy constructor and copy assignment because singleton
		 */
		EntityManager(EntityManager const&) = delete;
		EntityManager& operator=(EntityManager const&) = delete;

		/**
		 * @brief Create an entity.
		 * @return A reference to the entity.
		 */
		Entity& CreateEntity();

		/**
		 * @brief Get an entity from it's ID.
		 * @param[in] entityId ID of the entity
		 * @return A reference to the entity.
		 */
		Entity& GetEntity(EntityId entityId);

		/**
		 * @brief Destroy an entity.
		 * @paran[in] entity Reference to an entity
		 */
		void DestroyEntity(Entity const& entity);

		/**
		 * @brief Get the number of existing entities
		 * @return The number of entities
		 */
		size_t GetEntityCount() const;

		/**
		 * @brief Add component to entity
		 * @param entity Reference to entity
		 */
		template <typename T>
		void AddComponent(Entity& entity);

		/**
		 * @brief Add component to entity
		 * @param entity Reference to entity
		 * @param component fowarding reference to a component
		 */
		template <typename T>
		void AddComponent(Entity& entity, T&& component);

		/**
		 * @brief Remove component from entity
		 * @param entity Reference to entity
		 */
		template <typename T>
		void RemoveComponent(Entity& entity);

		/**
		 * @brief Get the reference to the component of an entity
		 * @param entity Reference to entity
		 */
		template <typename T>
		T* GetComponent(Entity const& entity, T** handle);

		/**
		 * @brief Set component data
		 * @param entity Reference to entity
		 * @param component fowarding reference to a component
		 */
		template <typename T>
		void SetComponent(Entity& entity, T&& component);

	private:
		EntityManager();
		uint32_t mIdCounter;
		std::vector<Entity> mEntities;
		std::unordered_map<EntityId, size_t> mEntityIdToIndexMap;
		std::unordered_map<size_t, EntityId> mIndexToEntityIdMap;
};

#include "Managers/EntityManager.ipp"

#endif // !ENTITY_MANAGER_HPP
