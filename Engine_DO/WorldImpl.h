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
    WorldImpl(Entity::EntityManager* i_em);
    Entity::EntityManager& GetEM();
    ~WorldImpl();

   private:
    Entity::EntityManager* d_em{nullptr};
};
}  // namespace World