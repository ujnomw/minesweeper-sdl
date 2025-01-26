#pragma once
#include <SDL.h>

namespace Engine
{

class Rectangle
{
   public:
    Rectangle(int x, int y, int w, int h, SDL_Color Color = {0, 0, 0, 255})
        : Rect{x, y, w, h}, Color{Color}
    {
    }

    virtual void Render(SDL_Surface *Surface)
    {
        SDL_FillRect(Surface, &Rect,
                     SDL_MapRGB(Surface->format, Color.r, Color.g, Color.b));
    }

    void SetColor(SDL_Color C) { Color = C; }

    bool IsWithinBounds(int x, int y) const
    {
        // Too far left
        if (x < Rect.x) return false;
        // Too far right
        if (x > Rect.x + Rect.w) return false;
        // Too high
        if (y < Rect.y) return false;
        // Too low
        if (y > Rect.y + Rect.h) return false;
        // Within bounds
        return true;
    }

   private:
    SDL_Rect Rect{0, 0, 0, 0};
    SDL_Color Color{0, 0, 0, 0};
};
}  // namespace Engine