#include "Button.h"

namespace Engine
{
Button::Button(int x, int y, int w, int h) : Rectangle{x, y, w, h, Config::BUTTON_COLOR}
{
}

void Button::HandleEvent(const SDL_Event &E)
{
    if (isDisabled) return;
    if (E.type == SDL_MOUSEMOTION)
    {
        HandleMouseMotion(E.motion);
    }
    else if (E.type == SDL_MOUSEBUTTONDOWN)
    {
        HandleMouseButton(E.button);
    }
}

void Button::SetIsDisabled(bool newValue) { isDisabled = newValue; }
void Button::HandleMouseEnter() { SetColor(Config::BUTTON_HOVER_COLOR); }

void Button::HandleMouseExit() { SetColor(Config::BUTTON_COLOR); }

void Button::HandleMouseMotion(const SDL_MouseMotionEvent &E)
{
    if (IsWithinBounds(E.x, E.y))
    {
        HandleMouseEnter();
    }
    else
    {
        HandleMouseExit();
    }
}
void Button::HandleMouseButton(const SDL_MouseButtonEvent &E)
{
    if (IsWithinBounds(E.x, E.y))
    {
        const Uint8 Button{E.button};
        if (Button == SDL_BUTTON_LEFT)
        {
            HandleLeftClick();
        }
        else if (Button == SDL_BUTTON_RIGHT)
        {
            HandleRightClick();
        }
    }
}
}  // namespace Engine