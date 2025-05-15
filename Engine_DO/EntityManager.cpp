#include "EntityManager.h"

#include <cassert>

#include "Globals.h"
namespace Entity
{

EntityManager* createManager(int i_maxEntities)
{
    auto* em = new EntityManager();
    em->entities.resize(i_maxEntities);
    em->ids.resize(i_maxEntities);
    em->children.resize(i_maxEntities);
    em->parents.resize(i_maxEntities);
    em->positions.resize(i_maxEntities);
    em->sizes.resize(i_maxEntities);
    return em;
}

bool createEntities(EntityCollection& i_entities, EntityIdCollection& i_ids,
                    EntityIdCollection& o_res, EntityId& nextId)
{
    if (o_res.empty() || i_ids.empty() || i_entities.empty()) return false;
    for (auto& o_id : o_res)
    {
        EntityId id = nextId++;
        i_ids[id] = id;
        i_entities[id] = Entity{id};
        o_id = id;
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

void setType(EntityCollection& entities, EntityIdCollection& i_ids, EntityType& i_type)
{
    for (auto& id : i_ids)
    {
        entities[id].d_type = i_type;
    }
}

void setSize(std::vector<Size>& sizes, EntityIdCollection& i_ids,
             std::vector<Size>& i_sizes)
{
    assert(i_ids.size() == i_sizes.size());

    for (int i = 0; i < i_ids.size(); i++)
    {
        auto i_id = i_ids[i];
        sizes[i_id] = i_sizes[i];
    }
}

void setPosition(std::vector<Position>& positions, EntityIdCollection& i_ids,
                 std::vector<Position>& i_positions)
{
    assert(i_ids.size() == i_positions.size());

    for (int i = 0; i < i_ids.size(); i++)
    {
        auto i_id = i_ids[i];
        positions[i_id] = i_positions[i];
    }
}

void computeLayout(EntityCollection& entities, std::vector<EntityIdCollection>& children,
                   std::vector<Size>& sizes, std::vector<Position>& positions,
                   EntityId rootId, Position rootPosition)
{
    // Asuming entities are sorted if not should be
    // Setting sizes
    std::vector<Size> newSizes;
    EntityIdCollection newSizeIds;
    int currentId = entities.size() - 1;
    int rootIdInt = rootId;
    while (currentId >= rootIdInt)
    {
        if (entities[currentId].d_type == "row")
        {
            int w = 0;
            int maxH = 0;
            for (auto childId : children[currentId])
            {
                w += sizes[childId].w;
                if (maxH < sizes[childId].h)
                {
                    maxH = sizes[childId].h;
                }
            }
            w += (children[currentId].size() - 1) * Config::PADDING;
            sizes[currentId] = {w, maxH};
            currentId--;
            continue;
        }
        if (entities[currentId].d_type == "column")
        {
            int maxW = 0;
            int H = 0;
            for (auto childId : children[currentId])
            {
                H += sizes[childId].h;
                if (maxW < sizes[childId].w)
                {
                    maxW = sizes[childId].w;
                }
            }
            H += (children[currentId].size() - 1) * Config::PADDING;
            sizes[currentId] = {maxW, H};
            currentId--;
            continue;
        }
        currentId--;
    }
    setSize(sizes, newSizeIds, newSizes);

    positions[rootId] = rootPosition;
    for (uint i = rootId; i < entities.size(); i++)
    {
        if (entities[i].d_type == "row")
        {
            uint nextXpos = positions[i].x;
            uint Y = positions[i].y;
            for (auto childId : children[i])
            {
                positions[childId].x = nextXpos;
                positions[childId].y = Y;
                nextXpos += sizes[childId].w + Config::PADDING;
            }
            continue;
        }
        if (entities[i].d_type == "column")
        {
            uint nextYpos = positions[i].y;
            uint X = positions[i].x;
            for (auto childId : children[i])
            {
                positions[childId].y = nextYpos;
                positions[childId].x = X;
                nextYpos += sizes[childId].h + Config::PADDING;
            }
            continue;
        }
    }
}
}  // namespace Entity