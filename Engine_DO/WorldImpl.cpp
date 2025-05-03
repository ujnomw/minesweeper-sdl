#include "WorldImpl.h"

#include "EntityManager.h"
namespace World
{
WorldImpl::WorldImpl(Entity::EntityManager* i_em) { d_em = i_em; }

Entity::EntityManager& WorldImpl::GetEM() { return *d_em; }

WorldImpl::~WorldImpl()
{
    if (d_em) delete d_em;
}
}  // namespace World