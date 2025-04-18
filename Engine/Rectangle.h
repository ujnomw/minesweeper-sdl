#pragma once
#include <SDL.h>

#include "UIElement.h"
namespace Engine
{

class Rectangle : public Layout::UIElement
{
   public:
    Rectangle() {}
    Rectangle(int x, int y, int w, int h, SDL_Color Color = {0, 0, 0, 255});

    virtual void Render(SDL_Surface *Surface) override;

    void SetColor(SDL_Color C);

    bool IsWithinBounds(int i_x, int i_y);

   private:
    SDL_Color Color{0, 0, 0, 0};
};
}  // namespace Engine