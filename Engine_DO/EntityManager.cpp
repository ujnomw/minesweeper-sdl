#include "EntityManager.h"

#include <cassert>

#include "Globals.h"
namespace Entity
{

EntityManager* createManager(int i_maxEntities)
{
    auto* em = new EntityManager();
    em->entities.resize(i_maxEntities);
    em->idsToIndexes.resize(i_maxEntities);
    em->children.resize(i_maxEntities);
    em->parents.resize(i_maxEntities);
    em->positions.resize(i_maxEntities);
    em->sizes.resize(i_maxEntities);
    return em;
}

bool createEntities(EntityCollection& i_entities, EntityIdCollection& i_ids,
                    std::vector<Position>& i_positions, std::vector<Size>& i_sizes,
                    EntityIdCollection& o_res, EntityId& nextId, int& nextIndex,
                    int i_count)
{
    if (i_ids.empty() || i_entities.empty() || i_count < 1) return false;
    for (int i = 0; i < i_count; i++)
    {
        EntityId id = nextId++;
        i_ids[id] = nextIndex++;
        int index = i_ids[id];
        i_entities[index] = Entity{id};
        i_positions[index] = Position{};
        i_sizes[index] = Size{};
        o_res.push_back(id);
    }
    return true;
}

void setParent(EntityIdCollection& parents, std::vector<EntityIdCollection>& children,
               EntityIdCollection& i_childrenIds, EntityId i_parentId)
{
    for (auto& c : i_childrenIds)
    {
        children[i_parentId].push_back(c);
        parents[c] = i_parentId;
    }
}

void setType(EntityCollection& entities, EntityIdCollection& idsToIndexes,
             EntityIdCollection& i_ids, EntityType& i_type)
{
    for (auto& id : i_ids)
    {
        int index = idsToIndexes[id];
        entities[index].d_type = i_type;
    }
}

void setSize(std::vector<Size>& sizes, EntityIdCollection& idsToIndexes,
             EntityIdCollection& i_ids, std::vector<Size>& i_sizes)
{
    assert(i_ids.size() == i_sizes.size());

    for (int i = 0; i < i_ids.size(); i++)
    {
        auto i_id = i_ids[i];
        int index = idsToIndexes[i_id];
        sizes[index] = i_sizes[i];
    }
}

void setPosition(std::vector<Position>& positions, EntityIdCollection& idsToIndexes,
                 EntityIdCollection& i_ids, std::vector<Position>& i_positions)
{
    assert(i_ids.size() == i_positions.size());

    for (int i = 0; i < i_ids.size(); i++)
    {
        auto i_id = i_ids[i];
        int index = idsToIndexes[i_id];
        positions[index] = i_positions[i];
    }
}

void computeLayout(EntityCollection& entities, EntityIdCollection& idsToIndexes,
                   std::vector<EntityIdCollection>& children, std::vector<Size>& sizes,
                   std::vector<Position>& positions, EntityId rootId,
                   Position rootPosition)
{
    // Asuming entities are sorted if not should be
    // Setting sizes
    std::vector<Size> newSizes;
    EntityIdCollection newSizeIds;
    int currentIndex = idsToIndexes.size() - 1;
    EntityId currentId;
    int rootIndex = idsToIndexes[rootId];
    int childIndex;
    while (currentIndex >= rootIndex)
    {
        currentId = idsToIndexes[currentIndex];
        if (entities[currentIndex].d_type == "row")
        {
            int w = 0;
            int maxH = 0;
            for (auto childId : children[currentId])
            {
                childIndex = idsToIndexes[childId];
                w += sizes[childIndex].w;
                if (maxH < sizes[childIndex].h)
                {
                    maxH = sizes[childIndex].h;
                }
            }
            w += (children[currentId].size() - 1) * Config::PADDING;
            sizes[currentIndex] = {w, maxH};
            currentIndex--;
            continue;
        }
        if (entities[currentIndex].d_type == "column")
        {
            int maxW = 0;
            int H = 0;
            for (auto childId : children[currentId])
            {
                childIndex = idsToIndexes[childId];
                H += sizes[childIndex].h;
                if (maxW < sizes[childIndex].w)
                {
                    maxW = sizes[childIndex].w;
                }
            }
            H += (children[currentIndex].size() - 1) * Config::PADDING;
            sizes[currentIndex] = {maxW, H};
            currentIndex--;
            continue;
        }
        currentIndex--;
    }
    setSize(sizes, idsToIndexes, newSizeIds, newSizes);

    positions[rootIndex] = rootPosition;
    for (uint i = rootIndex; i < entities.size(); i++)
    {
        if (entities[i].d_type == "row")
        {
            uint nextXpos = positions[i].x;
            uint Y = positions[i].y;
            for (auto childId : children[i])
            {
                childIndex = idsToIndexes[childId];
                positions[childIndex].x = nextXpos;
                positions[childIndex].y = Y;
                nextXpos += sizes[childIndex].w + Config::PADDING;
            }
            continue;
        }
        if (entities[i].d_type == "column")
        {
            uint nextYpos = positions[i].y;
            uint X = positions[i].x;
            for (auto childId : children[i])
            {
                childIndex = idsToIndexes[childId];
                positions[childIndex].y = nextYpos;
                positions[childIndex].x = X;
                nextYpos += sizes[childIndex].h + Config::PADDING;
            }
            continue;
        }
    }
}

EntityManager::~EntityManager()
{
    if (atlas)
    {
        SDL_DestroyTexture(atlas);
    }
}
}  // namespace Entity