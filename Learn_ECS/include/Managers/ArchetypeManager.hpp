/*************************************************************//**
 * @file   ArchetypeManager.hpp
 * @brief  Manager of all Archetypes
 *
 * Key features:
 * Is a Singleton
 * Create Archetypes
 * Destroy Archetypes
 * Get Archetypes
 * Add Entities to Archetypes
 * Remove Entities from Archetypes
 * Add components to Entity
 * Remove components from Entity
 * Copy components from Archetype to Archetype
 * Get Archetype Set (Archetypes that have common signatures)
 *
 * Usage:
 *
 * Dependencies:
 *
 * @author HONG Xian Xiang
 * @date   3rd October 2024
 * Copyright 2024, Digipen Institute of Technology
*****************************************************************/

#ifndef ARCHETYPE_MANAGER_HPP
#define ARCHETYPE_MANAGER_HPP

#include <iostream>
#include <unordered_map>
#include <vector>
#include <memory>
#include "Archetype.hpp"
#include "Entity.hpp"

class ArchetypeManager
{
	public:
		/**
		 * @brief Get the singleton instance
		 */
		static ArchetypeManager& GetInstance();

		/**
		 * @brief Delete copy constructor and copy assignment because singleton
		 */
		ArchetypeManager(ArchetypeManager const&) = delete;
		void operator=(ArchetypeManager const&) = delete;

		/**
		 * @brief Creates an archetype with a given signature. Doesn't do anything if archetype exists
		 * @param signature Signature of the Archetype to create
		 * @return Pointer to the created archetype, or nullptr.
		 */
		Archetype* CreateArchetype(Signature signature);

		/**
		 * @brief Get a shared pointer to desired archetype.
		 * @param signature Signature of the Archetype to get
		 * @return Pointer to the created archetype, or nullptr.
		 */
		Archetype* GetArchetype(Signature signature);

		/**
		 * @brief Destroy an archetype
		 * @param signature Signature of the Archetype
		 */
		void DestroyArchetype(Signature signature);

		/**
		 * @brief Add component data to an entity. This operation will move the entity to a new archetype.
		 * @param entity Reference to an entity
		 * @param component rvalue reference to component
		 */
		template <typename T>
		void AddComponent(Archetype* archetype, T&& component, Entity const& entity);

		/**
		 * @brief Remove component data from an entity. This operation will move the entity to a new archetype.
		 * @param entity Reference to an entity
		 */
		template <typename T>
		void RemoveComponent(Archetype* archetype, Entity const& entity);

		/**
		 * @brief Remove entity from archetype
		 * @param[in] entity Readonly reference to entity
		 */
		void RemoveEntity(Entity const& entity);

		/**
		 * @brief Get a vector of archetypes that shares common component types.
		 * @return Vector of shared pointers to archetype
		 */
		template <typename... T>
		ArchetypeSet GetArchetypeSet();

	private:
		ArchetypeManager();
		std::unordered_map<Signature, Archetype> mSignatureToArchetypeMap;
};

#include "ArchetypeManager.ipp"

#endif // ! ARCHETYPE_MANAGER_HPP
