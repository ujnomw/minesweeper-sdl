#include "FlagCounter.h"

#include "Globals.h"
#include "Minesweeper/GameSettings.h"
FlagCounter::FlagCounter()
    : Image{Config::FOOTER_HEIGHT - Config::PADDING,
            Config::FOOTER_HEIGHT - Config::PADDING, Config::FLAG_IMAGE,
            Config::FLAG_COUNTER_ICON_WIDTH},
      Text{0,
           0,
           Config::FLAG_COUNTER_WIDTH - Config::FOOTER_HEIGHT -
               Config::FLAG_COUNTER_ICON_WIDTH,
           Config::FOOTER_HEIGHT - Config::PADDING,
           std::to_string(GameSettings::BombCount()),
           {255, 255, 255, 255},
           20},
      FlagsAvailable{GameSettings::BombCount()}
{
    SetWH(Config::FLAG_COUNTER_WIDTH, Config::FOOTER_HEIGHT - Config::PADDING);
    SetColor(Config::FLAG_COUNTER_COLOR);
}

void FlagCounter::SetRect(SDL_Rect i_rect)
{
    Rectangle::SetRect(i_rect);
    Content.SetRect(i_rect);
}

void FlagCounter::Render(SDL_Surface* Surface)
{
    Rectangle::Render(Surface);
    Content.Render(Surface);
}

void FlagCounter::HandleEvent(const SDL_Event& E)
{
    if (E.type == UserEvents::FLAG_PLACED)
    {
        --FlagsAvailable;
    }
    else if (E.type == UserEvents::FLAG_CLEARED)
    {
        ++FlagsAvailable;
    }
    else if (E.type == UserEvents::GAME_WON)
    {
        FlagsAvailable = 0;
    }
    else if (E.type == UserEvents::NEW_GAME)
    {
        FlagsAvailable = GameSettings::BombCount();
    }
    else
    {
        return;
    }
    Text.SetText(std::to_string(FlagsAvailable));
}

void FlagCounter::ComputeLayout(int i_x, int i_y)
{
    UIElement::ComputeLayout(i_x, i_y);
    Content.ComputeLayout(i_x, i_y);
}