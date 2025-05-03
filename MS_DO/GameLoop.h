#pragma once

#include <SDL.h>

namespace Entity
{
struct EntityManager;
}

namespace GameLoop
{
extern void init(/**/);
extern void update(Entity::EntityManager& em, SDL_Event& i_event);
extern void render(Entity::EntityManager& em);
}  // namespace GameLoop