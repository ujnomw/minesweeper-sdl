#include "DifficultySwitch.h"

#include "GameSettings.h"

DifficultySwitch::DifficultySwitch()
    : d_refreshImage{Config::FOOTER_HEIGHT - Config::PADDING,
                     Config::FOOTER_HEIGHT - Config::PADDING, Config::REFRESH_IMAGE}
{
    SetWH(Config::FLAG_COUNTER_WIDTH, Config::FOOTER_HEIGHT - Config::PADDING);
    SetColor(Config::BUTTON_COLOR);
}

void DifficultySwitch::ComputeLayout(int i_x, int i_y)
{
    Button::ComputeLayout(i_x, i_y);
    auto [w, _h] = GetWH();
    auto [imageW, _imageH] = d_refreshImage.GetWH();
    int imageOffsetX = (w - imageW) / 2;
    d_refreshImage.ComputeLayout(i_x + imageOffsetX, i_y);
}

void DifficultySwitch::Render(SDL_Surface* i_surface)
{
    Button::Render(i_surface);
    d_refreshImage.Render(i_surface);
}

void DifficultySwitch::HandleLeftClick()
{
    GameSettings::SwitchNextMode();
    SDL_Event E{UserEvents::NEXT_DIFFICULTY_CHANGED};
    SDL_PushEvent(&E);
}
