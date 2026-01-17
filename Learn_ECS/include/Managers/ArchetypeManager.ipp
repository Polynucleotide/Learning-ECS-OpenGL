#include "Managers/ComponentManager.hpp"

/**
 * @brief Add component data to an entity. This operation will move the entity to a new archetype.
 * @param entity Reference to an entity
 * @param component rvalue reference to component
 */
template <typename T>
void ArchetypeManager::AddComponent(Archetype* archetype, T&& component, Entity const& entity)
{
	EntityId entityId{ entity.GetId() };
	archetype->AddEntity(entityId);
	archetype->SetComponent(entityId, std::move(component));

	Archetype* oldArchetype{ GetArchetype(entity.GetSignature()) };
	if (!oldArchetype) return;
	oldArchetype->MoveComponents(entityId, archetype);
	oldArchetype->RemoveEntity(entityId);
	oldArchetype = nullptr;
}

/**
 * @brief Remove component data from an entity. This operation will move the entity to a new archetype.
 * @param entity Reference to an entity
 */
template <typename T>
void ArchetypeManager::RemoveComponent(Archetype* archetype, Entity const& entity)
{
	EntityId entityId{ entity.GetId() };
	archetype->AddEntity(entityId);

	Archetype* oldArchetype{ GetArchetype(entity.GetSignature()) };
	if (!oldArchetype) return;
	oldArchetype->MoveComponents(entityId, archetype);
	oldArchetype->RemoveEntity(entityId);
	oldArchetype = nullptr;
}

/**
 * @brief Get a vector of archetypes that shares common component types.
 */
template <typename... T>
ArchetypeSet ArchetypeManager::GetArchetypeSet()
{
	// Holy shit what is this dark magic
	ComponentManager& cm{ ComponentManager::GetInstance() };
	Signature signature{ 0 };
	((signature |= cm.GetSignature<T>()), ...);

	ArchetypeSet archetypeSet;

	// TODO Reserve to MAX_COMPONENTS, completely arbitrary
	archetypeSet.reserve(MAX_COMPONENTS);
	for (auto& pair : mSignatureToArchetypeMap)
	{
		if ((pair.second.GetSignature() & signature) == signature)
			archetypeSet.push_back(&pair.second);
	}

	return archetypeSet;
}
