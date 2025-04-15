#pragma once

#include "Engine/Button.h"
#include "Engine/Image.h"

class DifficultySwitch : public Engine::Button
{
   public:
    DifficultySwitch();
    void ComputeLayout(int i_x, int i_y) override;
    void Render(SDL_Surface*) override;

   private:
    void HandleLeftClick() override;
    Engine::Image d_refreshImage;
};