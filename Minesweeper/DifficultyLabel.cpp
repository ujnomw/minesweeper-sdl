#include "DifficultyLabel.h"

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

void DifficultyLabel::HandleEvent(const SDL_Event& i_event)
{
    if (i_event.type == UserEvents::NEXT_DIFFICULTY_CHANGED)
    {
        d_text.SetText("LEVEL: " + GameSettings::GetNextMode());
    }
}
