#pragma once
#include "../Globals.h"
#include "Rectangle.h"

namespace Engine
{

class Button : public Rectangle
{
   public:
    Button(int x, int y, int w, int h) : Rectangle{x, y, w, h, Config::BUTTON_COLOR} {}

    void virtual HandleEvent(const SDL_Event &E)
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

   protected:
    virtual void HandleLeftClick() {}
    virtual void HandleRightClick() {}

    void SetIsDisabled(bool newValue) { isDisabled = newValue; }
    virtual void HandleMouseEnter() { SetColor(Config::BUTTON_HOVER_COLOR); }

    virtual void HandleMouseExit() { SetColor(Config::BUTTON_COLOR); }

    void HandleMouseMotion(const SDL_MouseMotionEvent &E)
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
    void HandleMouseButton(const SDL_MouseButtonEvent &E)
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

   private:
    bool isDisabled{false};
};
}  // namespace Engine