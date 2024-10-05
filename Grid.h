#pragma once

#include "Component.h"
#include <memory>
#include <vector>
#include <SDL.h>

class Grid
{
public:
    void AddChild(
        std::shared_ptr<Component> Child)
    {
        Children.push_back(Child);
    }

    void Render(SDL_Surface *Surface)
    {
        for (auto &Child : Children)
        {
            Child->Render(Surface);
        }
    }

    void HandleEvent(const SDL_Event &E)
    {
        for (auto &Child : Children)
        {
            Child->HandleEvent(E);
        }
    }

    std::vector<std::shared_ptr<Component>> Children;
};