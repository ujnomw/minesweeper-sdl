#pragma once
#include "Globals.h"
#include "Rectangle.h"
namespace Engine
{

class Button : public Rectangle
{
   public:
    Button() {}
    Button(int x, int y, int w, int h);

    void virtual HandleEvent(const SDL_Event &E);

   protected:
    virtual void HandleLeftClick() {}
    virtual void HandleRightClick() {}

    void SetIsDisabled(bool newValue);
    virtual void HandleMouseEnter();

    virtual void HandleMouseExit();

    void HandleMouseMotion(const SDL_MouseMotionEvent &E);
    void HandleMouseButton(const SDL_MouseButtonEvent &E);

   private:
    bool isDisabled{false};
};
}  // namespace Engine