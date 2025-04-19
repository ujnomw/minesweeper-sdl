#include "EntityManager.h"

namespace Entity
{
EntityId EntityManager::createEntity()
{
    EntityId id = nextId++;
    auto entity = Entity{id};
    entities[id] = entity;
    return id;
};
bool EntityManager::has(EntityId i_id) { return entities.contains(i_id); }
Entity& EntityManager::getEntity(EntityId i_id) { return entities[i_id]; };
bool EntityManager::remove(EntityId i_id) { return entities.erase(i_id); }
}  // namespace Entity