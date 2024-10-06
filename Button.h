#pragma once
#include "Rectangle.h"

class Button : public Rectangle
{
public:
    Button(int x, int y, int w, int h) : Rectangle{x, y, w, h, {0, 255, 0}} {}

    void HandleEvent(const SDL_Event &E)
    {
        if (isDisabled)
            return;
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

    void SetIsDisabled(bool newValue)
    {
        isDisabled = newValue;
    }
    virtual void HandleMouseEnter()
    {
        SetColor({255, 0, 0});
    }

    virtual void HandleMouseExit()
    {
        SetColor({0, 255, 0});
    }

private:
    void HandleMouseMotion(
        const SDL_MouseMotionEvent &E)
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
    void HandleMouseButton(
        const SDL_MouseButtonEvent &E)
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

    bool isDisabled{false};
};