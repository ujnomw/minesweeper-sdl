#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include <string>

#include "EntityID.h"

namespace Entity

{
struct EntityManager;
using EntityType = std::string;
struct Entity
{
    EntityId d_id;
    EntityType d_type;
    SDL_Rect d_rect{0, 0, 0, 0};

    // Rectangle fields
    SDL_Color d_backgroundColor{255, 255, 255, 255};

    // Text fields
    SDL_Surface* TextSurface{nullptr};
    TTF_Font* Font{nullptr};
    SDL_Rect TextPosition{0, 0, 0, 0};
    SDL_Color Color{0, 0, 0, 255};

    // Image fields
    SDL_Surface* ImageSurface{nullptr};
    SDL_Rect Destination{0, 0, 0, 0};
    int d_padding = 12;
    // Button fields
    bool isDisabled;
};
}  // namespace Entity
