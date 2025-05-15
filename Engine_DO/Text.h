#pragma once

#include <SDL.h>

#include <string>

#include "Entity.h"
#include "EntityID.h"

namespace Entity
{
struct EntityManager;
extern void createText(EntityManager& i_em, EntityId id, std::string& i_content,
                       SDL_Color i_color = {0, 0, 0, 255}, int i_fontSize = 30,
                       Size i_size = {0, 0});
extern void renderTexts(EntityManager& i_em, SDL_Renderer* i_renderer,
                        EntityIdCollection& i_ids);
}  // namespace Entity
