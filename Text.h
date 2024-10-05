#pragma once

#include <SDL.h>
#include "Rectangle.h"

class Text : public Rectangle
{
public:
    Text(int x, int y, int w, int h)
        : Rect{x, y, w, h} {}

    void Render(SDL_Surface *Surface)
    {
        Rectangle::Render(Surface);
        // Render Text...
    }
};