#pragma once

#include "Engine/Button.h"
#include "Engine/Text.h"
#include "Globals.h"

class NewGameButton : public Engine::Button
{
   public:
    NewGameButton(int x, int y, int w, int h)
        : Button{x, y, w, h}, Text{x, y, w, h, "NEW GAME", {}, 20}
    {
    }

    NewGameButton()
        : Text{0,
               0,
               Config::NEW_GAME_BUTTON_WIDTH,
               Config::FOOTER_HEIGHT - Config::PADDING,
               "NEW GAME",
               {50, 50, 50},
               20}
    {
        SetRect({0, 0,
                 Config::WINDOW_WIDTH - Config::PADDING * 3 - Config::FLAG_COUNTER_WIDTH,
                 Config::FOOTER_HEIGHT - Config::PADDING});
        SetColor(Config::BUTTON_COLOR);
    }

    void SetRect(SDL_Rect i_rect) override
    {
        Button::SetRect(i_rect);
        Text.SetRect(i_rect);
    }

    void ComputeLayout(int i_x, int i_y) override
    {
        UIElement::ComputeLayout(i_x, i_y);
        Text.ComputeLayout(i_x, i_y);
    }

    void Render(SDL_Surface* Surface) override
    {
        Button::Render(Surface);
        Text.Render(Surface);
    }

    void HandleLeftClick() override
    {
        SDL_Event E{UserEvents::NEW_GAME};
        SDL_PushEvent(&E);
    }

   private:
    Engine::Text Text;
};