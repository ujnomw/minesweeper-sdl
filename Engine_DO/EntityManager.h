#pragma once

#include <unordered_map>
#include <vector>

#include "Entity.h"
namespace Entity
{
struct EntityManager
{
    std::unordered_map<EntityId, Entity> entities;
    EntityId nextId = 1;
    EntityId createEntity();
    Entity& getEntity(EntityId);
    bool has(EntityId);
    bool remove(EntityId);
};
}  // namespace Entity