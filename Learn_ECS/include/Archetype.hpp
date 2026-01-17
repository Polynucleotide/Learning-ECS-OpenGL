/*************************************************************//**
 * @file   Archetype.hpp
 * @brief  Archetype is a combination of components.
 *
 * Key features:
 * Add an entity to the archetype
 * Remove an entity from the archetype
 * Get the number of entity that belongs in the archetype
 * Add component to the archetype
 * Copy components from archetype to archetype
 * Stores an array of each component
 *
 * Usage:
 * ArchetypeManager will call the functions in this class.
 * Get a specific archetype from ArchetypeManager.
 * Archetype archetype = ArchetypeManager::archetypes[signature]
 * archetype.AddComponent(entityId, component)
 *
 * Dependencies:
 *
 * @author HONG Xian Xiang
 * @date   3rd October 2024
 * Copyright 2024, Digipen Institute of Technology
*****************************************************************/

#ifndef ARCHETYPE_HPP
#define ARCHETYPE_HPP

#include <unordered_map>
#include "Alias.hpp"

class Archetype
{
	public:
		/**
		 * @brief Constructor
		 */
		Archetype() = default;
		Archetype(Signature signature);

		/**
		 * @brief Get the signature of the archetype
		 * @return Signature of the archetype
		 */
		Signature GetSignature() const;

		/**
		 * @brief Get the number of entities that belong in this archetype
		 * @return Number of entities
		 */
		size_t GetEntityCount() const;

		/**
		 * @brief Adds an entity to Archetype
		 * @param entityId Entity member id
		 */
		void AddEntity(EntityId entityId);

		/**
		 * @brief Removes an entity from Archetype
		 * @param entityId Entity member id
		 */
		void RemoveEntity(EntityId entityId);

		/**
		 * @brief Set component of an entity
		 * @param entityId Entity member id
		 * @param component rvalue reference to a component
		 */
		template <typename T>
		void SetComponent(EntityId entityId, T&& component);

		/**
		 * @brief Get the reference to the component of an entity
		 * @param[in] entityId Entity member id
		 * @param[in] componentSignature Signature of component of type T
		 */
		template <typename T>
		T* GetComponent(EntityId entityId, Signature componentSignature);

		/**
		 * @brief Get component array of type T
		 * @return Reference to component array
		 */
		template <typename T>
		ComponentArray& GetComponentArray();
		ComponentArray& GetComponentArray(Signature componentSignature);

		/**
		 * @brief Copy component data from an archetype to another
		 * @param entityId Entity member id
		 * @param to Pointer to the archetype
		 */
		void MoveComponents(EntityId entityId, Archetype* to);

		size_t GetIndexFromEntityId(EntityId entityId);

		/**
		 * @brief Displays the component vectors
		 */
		void PrintArchetype() const;

	private:
		Signature mSignature{0};
		std::unordered_map<Signature, ComponentArray> mSignatureToComponentArrMap;
		std::unordered_map<EntityId, size_t> mEntityIdToIndexMap;
		std::unordered_map<size_t, EntityId> mIndexToEntityIdMap;
};

std::ostream& operator<<(std::ostream& os, Archetype const& archetype);

#include "Archetype.ipp"

#endif // ! ARCHETYPE_HPP
