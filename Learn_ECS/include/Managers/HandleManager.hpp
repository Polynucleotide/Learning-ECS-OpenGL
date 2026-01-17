/*************************************************************//**
 * @file   HandleManager.hpp
 * @brief  Manager of component handles
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

#ifndef HANDLE_MANAGER_HPP
#define HANDLE_MANAGER_HPP

#include <unordered_map>
#include "Entity.hpp"
#include "Alias.hpp"

class HandleManager
{
	public:
		/**
		 * @brief Get singleton instance
		 * @return Reference to singleton
		 */
		static HandleManager& GetInstance()
		{
			static HandleManager instance;
			return instance;
		}

		HandleManager(HandleManager const&) = delete;
		HandleManager& operator=(HandleManager const&) = delete;

		/**
		 * @brief Add a handle
		 * Whenever the component held by an entity shifts, update its pointer.
		 * @param[in] entityId Entity ID
		 * @param[in] componentSignature Signature of the specific component.
		 * @param[in,out] handle Pointer to the pointer to the component. lol.
		 */
		void AddHandle(EntityId entityId, Signature componentSignature, void** handle);

		/**
		 * @brief Update component handle
		 * @param[in] entity Readonly reference to entity
		 */
		void UpdateEntityHandles(Entity const& entity);

		/**
		 * @brief Sets all handles to a detroyed entity to nullptr
		 * @param[in] entity Readonly reference to entity
		 */
		void DestroyEntityHandles(Entity const& entity);

	private:
		HandleManager() = default;
		std::unordered_map<EntityId, std::unordered_map<Signature, void**>> mEntityIdToHandleMap;
};

#endif // !HANDLE_MANAGER_HPP
