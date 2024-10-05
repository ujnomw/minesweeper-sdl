#pragma once

#include <SDL.h>

#include "Grid.h"
#include "Shapes.h"

class UI
{
public:
    UI()
    {
        GridComponent.AddChild(
            std::make_shared<Rectangle>());
        GridComponent.AddChild(
            std::make_shared<Circle>());
    }

    void Render(SDL_Surface *Surface)
    {
        GridComponent.Render(Surface);
    }

    void HandleEvent(const SDL_Event &E)
    {
        GridComponent.HandleEvent(E);
    }

private:
    Grid GridComponent;
};