#include <iostream>
#include "Managers/ComponentManager.hpp"

/**
 * @brief Set component of an entity
 * @param entityId Entity member id
 * @param component rvalue reference to a component
 */
template <typename T>
void Archetype::SetComponent(EntityId entityId, T&& component)
{
	Signature componentSignature{ ComponentManager::GetInstance().GetSignature<T>() };
	auto itComponent{ mSignatureToComponentArrMap.find(componentSignature) };
	if (itComponent == std::end(mSignatureToComponentArrMap))
	{
		std::cout << __FUNCTION__ << " Component (" << componentSignature << ": " << typeid(T).name() << ") not found.\n";
		return;
	}
	mSignatureToComponentArrMap[componentSignature][mEntityIdToIndexMap[entityId]] = std::move(component);
}

/**
 * @brief Get the reference to the component of an entity
 * @param[in] entityId Entity member id
 * @param[in] componentSignature Signature of component of type T
 */
template <typename T>
T* Archetype::GetComponent(EntityId entityId, Signature componentSignature)
{
	if ((componentSignature & mSignature) == 0) return nullptr;
	size_t index{ mEntityIdToIndexMap[entityId] };
	return &std::any_cast<T&>(mSignatureToComponentArrMap[componentSignature][index]);
}

/**
 * @brief Get component array of type T
 * @return Reference to component array
 */
template <typename T>
ComponentArray& Archetype::GetComponentArray()
{
	Signature componentSignature{ ComponentManager::GetInstance().GetSignature<T>() };
	return GetComponentArray(componentSignature);
}
