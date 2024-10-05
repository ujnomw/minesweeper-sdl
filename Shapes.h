#pragma once
#include <iostream>
#include <SDL.h>
#include "Component.h"

class Rectangle : public Component
{
    void Render(SDL_Surface *Surface) override
    {
        std::cout << "Rendering Rectangle\n";
    }
};

class Circle : public Component
{
    void Render(SDL_Surface *Surface) override
    {
        std::cout << "Rendering Circle\n";
    }
};