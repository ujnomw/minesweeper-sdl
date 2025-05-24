#pragma once

#include <SDL.h>

namespace Entity
{
struct EntityManager;
}

namespace GameLoop
{
extern bool init(Entity::EntityManager* em);
extern void update(Entity::EntityManager& em, SDL_Event& i_event);
extern void render(Entity::EntityManager& em, SDL_Renderer* i_renderer);
}  // namespace GameLoop