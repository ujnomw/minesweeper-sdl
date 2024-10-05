#pragma once

#include <SDL.h>

class Rectangle
{
public:
    Rectangle(int x, int y, int w, int h)
        : Rect{x, y, w, h} {}

    void Render(SDL_Surface *Surface)
    {
        SDL_FillRect(
            Surface, &Rect, SDL_MapRGB(Surface->format, 255, 0, 0));
    }

private:
    SDL_Rect Rect{0, 0, 0, 0};
};