#include <iostream>
#include "Interfaces/IComponent.hpp"
#include "Managers/ArchetypeManager.hpp"
#include "Managers/ComponentManager.hpp"
#include "Managers/HandleManager.hpp"

/**
 * @brief Add component to entity
 * @param entity Reference to entity
 */
template <typename T>
void EntityManager::AddComponent(Entity& entity)
{
	AddComponent(entity, T{});
}

/**
 * @brief Add component to entity
 * @param entity Reference to entity
 * @param component rvalue reference to a component
 */
template <typename T>
void EntityManager::AddComponent(Entity& entity, T&& component)
{
	Signature componentSignature{ ComponentManager::GetInstance().GetSignature<T>() };
	Signature oldArchSignature{ entity.GetSignature() };
	Signature newArchSignature{ oldArchSignature | componentSignature };

	// If entity already has the component
	if (newArchSignature == oldArchSignature) return;

	ArchetypeManager& am{ ArchetypeManager::GetInstance() };
	Archetype* newArchetype{ am.CreateArchetype(newArchSignature) };
	if (newArchetype == nullptr)
	{
		std::cout << __FUNCTION__ << " Failed to create Archetype: " << newArchSignature << std::endl;
		return;
	}

	static_cast<IComponent&>(component).entityId = entity.GetId();
	am.AddComponent(newArchetype, std::move(component), entity);
	entity.SetSignature(newArchSignature);
	HandleManager::GetInstance().UpdateEntityHandles(entity);
}

/**
 * @brief Remove component from entity
 * @param entity Reference to entity
 */
template <typename T>
void EntityManager::RemoveComponent(Entity& entity)
{
	Signature componentSignature{ ComponentManager::GetInstance().GetSignature<T>() };
	Signature oldArchSignature{ entity.GetSignature() };

	// If entity doesn't have the component
	if ((oldArchSignature & componentSignature) == 0) return;

	Signature newArchSignature{ oldArchSignature ^ componentSignature };
	ArchetypeManager& am{ ArchetypeManager::GetInstance() };
	Archetype* newArchetype{ am.CreateArchetype(newArchSignature) };
	if (newArchetype == nullptr)
	{
		std::cout << __FUNCTION__ << " Archetype: " << newArchSignature << " not found.\n";
		return;
	}

	am.RemoveComponent<T>(newArchetype, entity);
	entity.SetSignature(newArchSignature);
	HandleManager::GetInstance().UpdateEntityHandles(entity);
}

/**
 * @brief Get the reference to the component of an entity
 * @param entity Reference to entity
 * @param[in] handle Handle of the pointer to the component
 */
template <typename T>
T* EntityManager::GetComponent(Entity const& entity, T** handle)
{
	EntityId entityId{ entity.GetId() };
	Signature componentSignature{ ComponentManager::GetInstance().GetSignature<T>() };
	HandleManager::GetInstance().AddHandle(entityId, componentSignature, reinterpret_cast<void**>(handle));

	ArchetypeManager& am{ ArchetypeManager::GetInstance() };
	Archetype* archetype{ am.GetArchetype(entity.GetSignature()) };
	return archetype->GetComponent<T>(entityId, componentSignature);
}

/**
 * @brief Set component data
 * @param entity Reference to entity
 * @param component fowarding reference to a component
 */
template <typename T>
void EntityManager::SetComponent(Entity& entity, T&& component)
{
	ArchetypeManager& am{ ArchetypeManager::GetInstance() };
	Archetype* archetype{ am.GetArchetype(entity.GetSignature()) };
	EntityId entityId{ entity.GetId() };
	return archetype->SetComponent(entityId, std::move(component));
}
