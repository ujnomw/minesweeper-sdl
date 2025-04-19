#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include <string>

#include "EntityID.h"

namespace Entity

{
struct Entity
{
    EntityId d_id;
    SDL_Rect d_rect;
    std::string d_type;

    // Rectangle fields
    SDL_Color d_backgroundColor;

    // Button fields
    bool isDisabled;

    // Text fields
    SDL_Surface* TextSurface{nullptr};
    TTF_Font* Font{nullptr};
    SDL_Rect TextPosition{0, 0, 0, 0};
    SDL_Color Color{0, 0, 0, 255};

    // Image fields
    SDL_Surface* ImageSurface{nullptr};
    SDL_Rect Destination{0, 0, 0, 0};
    int d_padding = 12;
};
}  // namespace Entity
