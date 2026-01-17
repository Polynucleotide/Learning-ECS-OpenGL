/*************************************************************//**
 * @file   ComponentManager.hpp
 * @brief  Manager of all Components
 *
 * Key features:
 * Is a Singleton
 * Register new components to the system
 * Get the signature of a particular component
 * Keeps track of the number of existing components
 *
 * Usage:
 * Register components to the system. Unregistered components can't be used.
 * Convert types into bitsets. e.g. Passing type "Transform" returns 0000 0000 0000 0001
 *
 * Dependencies:
 *
 * @author HONG Xian Xiang
 * @date   3rd October 2024
 * Copyright 2024, Digipen Institute of Technology
*****************************************************************/

#ifndef COMPONENT_MANAGER_HPP
#define COMPONENT_MANAGER_HPP

#include <typeindex>
#include <unordered_map>
#include "Alias.hpp"

class ComponentManager
{
	public:
		/**
		 * @brief Get the singleton instance
		 */
		static ComponentManager& GetInstance();

		/**
		 * @brief Delete copy constructor and copy assignment because singleton
		 */
		ComponentManager(ComponentManager const&) = delete;
		ComponentManager& operator=(ComponentManager const&) = delete;

		/**
		 * @brief Register components
		 */
		void Init();

		/**
		 * @brief Register a component type. If component type is not registered, it cannot be used.
		 */
		template <typename T>
		void RegisterComponent();

		/**
		 * @brief Gets the signature of a component type.
		 * @return Signature of the component of type T.
		 */
		template <typename T>
		Signature GetSignature();

	private:
		ComponentManager();
		std::unordered_map<std::type_index, Signature> mTypeToSignatureMap;
};

#include "ComponentManager.ipp"

#endif
