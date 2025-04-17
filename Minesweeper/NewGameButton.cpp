#include "NewGameButton.h"

#include "Globals.h"
#include "Minesweeper/GameSettings.h"
NewGameButton::NewGameButton(int x, int y, int w, int h)
    : Button{x, y, w, h}, Text{x, y, w, h, "NEW GAME", {}, 20}
{
}

NewGameButton::NewGameButton()
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
};

void NewGameButton::SetRect(SDL_Rect i_rect)
{
    Button::SetRect(i_rect);
    Text.SetRect(i_rect);
}

void NewGameButton::ComputeLayout(int i_x, int i_y)
{
    UIElement::ComputeLayout(i_x, i_y);
    Text.ComputeLayout(i_x, i_y);
}

void NewGameButton::Render(SDL_Surface* Surface)
{
    Button::Render(Surface);
    Text.Render(Surface);
}

void NewGameButton::HandleLeftClick()
{
    if (GameSettings::IsModeChanged())
    {
        SDL_Event E{UserEvents::DIFFICULTY_CHANGED};
        SDL_PushEvent(&E);
    }
    SDL_Event E{UserEvents::NEW_GAME};
    SDL_PushEvent(&E);
}
