#pragma once
#include <SDL.h>

namespace UserEvents_NS
{
    const inline Uint32 OPEN_SETTINGS{SDL_RegisterEvents(1)};
    const inline Uint32 CLOSE_SETTINGS{SDL_RegisterEvents(1)};
}