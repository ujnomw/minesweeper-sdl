#pragma once
#include <SDL.h>

#include "Layout/Box.h"

namespace Engine
{

class Rectangle
{
   public:
    Rectangle(int x, int y, int w, int h, SDL_Color Color = {0, 0, 0, 255})
        : d_box{x, y, w, h}, Color{Color}
    {
    }

    virtual void Render(SDL_Surface *Surface)
    {
        SDL_FillRect(Surface, &d_box.GetBoundsRef(),
                     SDL_MapRGB(Surface->format, Color.r, Color.g, Color.b));
    }

    void SetColor(SDL_Color C) { Color = C; }

    bool IsWithinBounds(int x, int y) const
    {
        const auto bounds = d_box.GetBounds();
        // Too far left
        if (x < bounds.x) return false;
        // Too far right
        if (x > bounds.x + bounds.w) return false;
        // Too high
        if (y < bounds.y) return false;
        // Too low
        if (y > bounds.y + bounds.h) return false;
        // Within bounds
        return true;
    }

   private:
    // SDL_Rect Rect{0, 0, 0, 0};
    Layout::Box d_box;
    SDL_Color Color{0, 0, 0, 0};
};
}  // namespace Engine