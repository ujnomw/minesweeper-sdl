#pragma once
#include <SDL.h>

#include "UIElement.h"
namespace Engine
{

class Rectangle : public Layout::UIElement
{
   public:
    Rectangle() {}
    Rectangle(int x, int y, int w, int h, SDL_Color Color = {0, 0, 0, 255}) : Color{Color}
    {
        SetRect({x, y, w, h});
    }

    virtual void Render(SDL_Surface *Surface) override
    {
        SDL_FillRect(Surface, &GetRect(),
                     SDL_MapRGB(Surface->format, Color.r, Color.g, Color.b));
    }

    void SetColor(SDL_Color C) { Color = C; }

    bool IsWithinBounds(int i_x, int i_y)
    {
        auto [x, y, w, h] = GetRect();
        // Too far left
        if (i_x < x) return false;
        // Too far right
        if (i_x > x + w) return false;
        // Too high
        if (i_y < y) return false;
        // Too low
        if (i_y > y + h) return false;
        // Within bounds
        return true;
    }

   private:
    SDL_Color Color{0, 0, 0, 0};
};
}  // namespace Engine