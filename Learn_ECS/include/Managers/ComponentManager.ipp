#include <iostream>
#include <exception>
#include <type_traits>
#include "Components/MonoBehaviour.hpp"

/**
 * @brief Register a component type. If component type is not registered, it cannot be used.
 */
template <typename T>
void ComponentManager::RegisterComponent()
{
	std::type_index type{ std::type_index(typeid(T)) };
	if (mTypeToSignatureMap.find(type) == std::end(mTypeToSignatureMap))
	{
		Signature signature{ 1ull << mTypeToSignatureMap.size() };
		mTypeToSignatureMap[type] = signature;
		std::cout << "Component Registered (" << mTypeToSignatureMap[type] << ": " << type.name() << ")\n";
	}
}

/**
 * @brief Gets the signature of a component type.
 */
template <typename T>
Signature ComponentManager::GetSignature()
{
	std::type_index type{ std::type_index(typeid(T)) };

	if (std::is_base_of<MonoBehaviour, T>::value)
		type = std::type_index(typeid(MonoBehaviour));

	auto it{ mTypeToSignatureMap.find(type) };
	if (it == std::end(mTypeToSignatureMap))
		throw std::exception{ "Component not found." };
	return it->second;
}
