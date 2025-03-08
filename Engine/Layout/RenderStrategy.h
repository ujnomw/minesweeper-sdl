#pragma once
#include "SDL.h"

namespace Layout
{

template <typename T>
class RenderStrategy
{
   public:
    virtual ~RenderStrategy() = default;
    virtual void Render(T &, SDL_Surface *) const = 0;
};
}  // namespace Layout
