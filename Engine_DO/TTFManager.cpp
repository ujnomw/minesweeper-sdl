#include "TTFManager.h"

#include <SDL_ttf.h>

#include <stdexcept>
namespace FontSystem
{
TTFManager::TTFManager()
{
    if (TTF_Init() != 0)
    {
        throw std::runtime_error("TTF_Init failed");
    }
}

TTFManager::~TTFManager() { TTF_Quit(); }
}  // namespace FontSystem