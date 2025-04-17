#pragma once

#include "Engine/Image.h"
#include "Engine/Rectangle.h"
#include "Engine/Text.h"

class FlagCounter : public Engine::Rectangle
{
   public:
    FlagCounter();

    void SetRect(SDL_Rect i_rect) override;

    void Render(SDL_Surface* Surface) override;
    void HandleEvent(const SDL_Event& E);

    void ComputeLayout(int i_x, int i_y) override;

   private:
    Engine::Image Image;
    Engine::Text Text;
    Engine::Layout::Row Content{Image, Text};
    int FlagsAvailable;
};