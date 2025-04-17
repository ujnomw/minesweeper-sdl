#pragma once

#include "Engine/Button.h"
#include "Engine/Text.h"

class NewGameButton : public Engine::Button
{
   public:
    NewGameButton(int x, int y, int w, int h);

    NewGameButton();

    void SetRect(SDL_Rect i_rect) override;

    void ComputeLayout(int i_x, int i_y) override;

    void Render(SDL_Surface* Surface) override;

    void HandleLeftClick() override;

   private:
    Engine::Text Text;
};