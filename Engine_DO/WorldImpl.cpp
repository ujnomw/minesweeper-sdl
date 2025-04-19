#include "WorldImpl.h"

#include "EntityManager.h"
namespace World
{
WorldImpl::WorldImpl() { d_em = std::make_shared<Entity::EntityManager>(); }
}  // namespace World