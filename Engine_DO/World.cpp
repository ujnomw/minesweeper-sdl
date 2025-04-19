#include "World.h"

#include "WorldImpl.h"
namespace World
{
World::World() { d_worldImpl = new WorldImpl(); }
WorldImpl& World::Get() { return *d_worldImpl; }
World::~World() { delete d_worldImpl; }
}  // namespace World