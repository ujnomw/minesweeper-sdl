#pragma once
#include <SDL.h>

#include <string>

#include "EntityID.h"
namespace Entity
{
struct EntityManager;
extern void createImage(EntityManager& em, EntityId i_id, const std::string& i_filename);
extern void renderImages(EntityManager& em, SDL_Renderer* i_renderer,
                         EntityIdCollection& i_ids);
}  // namespace Entity