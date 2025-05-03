#pragma once

#include <unordered_map>
#include <vector>

#include "Entity.h"
namespace Entity
{
using EntityCollection = std::vector<Entity>;
using EntityIdCollection = std::vector<EntityId>;
struct Position
{
    uint x = 0;
    uint y = 0;
};

struct Size
{
    uint w = 0;
    uint h = 0;
};
struct EntityManager
{
    EntityCollection entities;
    // id -> index in ^^^^^^^^^^
    EntityIdCollection ids;

    EntityIdCollection parents;
    std::vector<EntityIdCollection> children;

    std::vector<Position> positions;
    std::vector<Size> sizes;

    EntityId nextId = 0;
};

extern EntityManager createManager(uint);

extern bool createEntities(EntityCollection& i_entities, EntityIdCollection& i_ids,
                           EntityIdCollection& o_res, EntityId& nextId);

extern void setParent(EntityIdCollection& parents,
                      std::vector<EntityIdCollection>& children,
                      EntityIdCollection& i_children, EntityId i_parent);

extern void setType(EntityCollection& entities, EntityIdCollection& i_ids,
                    EntityType& i_type);

extern void setSize(std::vector<Size>& sizes, EntityIdCollection& i_ids,
                    std::vector<Size>& i_sizes);

extern void setPosition(std::vector<Position>& positions, EntityIdCollection& i_ids,
                        std::vector<Position>& i_positions);

extern void computeLayout(EntityCollection& entities,
                          std::vector<EntityIdCollection>& children,
                          std::vector<Size>& sizes, std::vector<Position>& positions,
                          EntityId rootId, Position rootPosition);
}  // namespace Entity