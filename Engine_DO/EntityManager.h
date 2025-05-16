#pragma once

#include <unordered_map>
#include <vector>

#include "Entity.h"
namespace Entity
{
using EntityCollection = std::vector<Entity>;
using EntityIdCollection = std::vector<EntityId>;

struct EntityManager
{
    EntityCollection entities;
    // id -> index in ^^^^^^^^^^ and all components
    EntityIdCollection idsToIndexes;

    EntityIdCollection parents;
    std::vector<EntityIdCollection> children;

    std::vector<Position> positions;
    std::vector<Size> sizes;

    EntityId nextId{0};

    // For overriding, deleting elements
    int nextIndex{0};
    SDL_Texture* atlas{nullptr};
    ~EntityManager();
};

extern EntityManager* createManager(int);

extern bool createEntities(EntityCollection& i_entities,
                           EntityIdCollection& i_idsToIndexes,
                           std::vector<Position>& i_positions, std::vector<Size>& sizes,
                           EntityIdCollection& o_res, EntityId& nextId, int& nextIndex,
                           int i_count);

extern void setParent(EntityIdCollection& parents,
                      std::vector<EntityIdCollection>& children,
                      EntityIdCollection& i_children, EntityId i_parent);

extern void setType(EntityCollection& entities, EntityIdCollection& idsToIndexes,
                    EntityIdCollection& i_ids, EntityType& i_type);

extern void setSize(std::vector<Size>& sizes, EntityIdCollection& idsToIndexes,
                    EntityIdCollection& i_ids, std::vector<Size>& i_sizes);

extern void setPosition(std::vector<Position>& positions,
                        EntityIdCollection& idsToIndexes, EntityIdCollection& i_ids,
                        std::vector<Position>& i_positions);

extern void computeLayout(EntityCollection& entities, EntityIdCollection& idsToIndexes,
                          std::vector<EntityIdCollection>& children,
                          std::vector<Size>& sizes, std::vector<Position>& positions,
                          EntityId rootId, Position rootPosition);
}  // namespace Entity