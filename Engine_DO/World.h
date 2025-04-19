#pragma once
namespace World
{
class WorldImpl;
class World
{
   private:
    WorldImpl* d_worldImpl;

   public:
    World();
    WorldImpl& Get();
    ~World();
};
}  // namespace World