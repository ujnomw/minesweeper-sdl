#include "World.h"

#include "WorldImpl.h"
namespace World
{
World::World(WorldImpl& i_worldImpl) : d_worldImpl{i_worldImpl} {}
WorldImpl& World::Get() { return d_worldImpl; }
World::~World() {}
}  // namespace World