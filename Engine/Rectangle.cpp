#include "Rectangle.h"

namespace Engine
{
Rectangle::Rectangle(int x, int y, int w, int h, SDL_Color Color) : Color{Color}
{
    SetRect({x, y, w, h});
}

void Rectangle::Render(SDL_Surface *Surface)
{
    SDL_FillRect(Surface, &GetRect(),
                 SDL_MapRGB(Surface->format, Color.r, Color.g, Color.b));
}

void Rectangle::SetColor(SDL_Color C) { Color = C; }

bool Rectangle::IsWithinBounds(int i_x, int i_y)
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
}  // namespace Engine