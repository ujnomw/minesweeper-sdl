#pragma once
#include <memory>
namespace Entity
{
class EntityManager;
}

namespace World
{
class WorldImpl
{
   public:
    WorldImpl();

   private:
    std::shared_ptr<Entity::EntityManager> d_em;
};
}  // namespace World