#pragma once

#include "Engine/Rectangle.h"
#include "Engine/Text.h"
#include "Globals.h"
#include "Minesweeper/GameSettings.h"

class DifficultyLabel : public Engine::Rectangle
{
   public:
    DifficultyLabel()
        : d_text{0,
                 0,
                 Config::DIFFICULTY_LABEL_WIDTH,
                 Config::FOOTER_HEIGHT - Config::PADDING,
                 "LEVEL: " + GameSettings::GetNextMode(),
                 {50, 50, 50},
                 20}
    {
        SetWH(Config::DIFFICULTY_LABEL_WIDTH, Config::FOOTER_HEIGHT - Config::PADDING);
        SetColor({176, 170, 170});
    };
    void Render(SDL_Surface *) override;
    void ComputeLayout(int i_x, int i_y) override;
    void SetRect(SDL_Rect i_rect) override;
    void HandleEvent(const SDL_Event &);

   private:
    Engine::Text d_text;
};