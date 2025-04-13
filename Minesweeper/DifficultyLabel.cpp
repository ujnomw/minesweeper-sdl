#include "DifficultyLabel.h"

// DifficultyLabel::DifficultyLabel()
//     : d_text{
//           0,
//           0,
//           GameSettings::WindowWidth() - Config::PADDING * 3 -
//           Config::FLAG_COUNTER_WIDTH, Config::FOOTER_HEIGHT - Config::PADDING,
//           GameSettings::GetNextMode(),
//           {50, 50, 50},
//           20}
// {
//     SetWH(GameSettings::WindowWidth() - Config::PADDING * 3 -
//     Config::FLAG_COUNTER_WIDTH,
//           Config::FOOTER_HEIGHT - Config::PADDING);
//     SetColor({255, 255, 255});
// };

void DifficultyLabel::Render(SDL_Surface* i_surface)
{
    Rectangle::Render(i_surface);
    d_text.Render(i_surface);
};

void DifficultyLabel::ComputeLayout(int i_x, int i_y)
{
    UIElement::ComputeLayout(i_x, i_y);
    d_text.ComputeLayout(i_x, i_y);
};

void DifficultyLabel::SetRect(SDL_Rect i_rect)
{
    Rectangle::SetRect(i_rect);
    d_text.SetRect(i_rect);
};
