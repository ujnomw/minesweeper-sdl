#pragma once

#include <SDL.h>

#include <string>
#include <utility>

#include "EventReceiver.h"
namespace Engine::Layout
{
using BoundsPair = std::pair<int, int>;
class IBox
{
   public:
    virtual ~IBox() = default;
    virtual SDL_Rect& GetRect() = 0;
    virtual void SetRect(SDL_Rect) = 0;
    virtual void Render(SDL_Surface*) = 0;
};

class UIElement : public IBox
{
   public:
    UIElement() {};
    void SetRect(SDL_Rect i_rect) override;

    SDL_Rect& GetRect() override;

    virtual void SetWH(int w, int h);

    virtual void SetXY(int x, int y);

    BoundsPair GetWH();

    BoundsPair GetXY();

    virtual std::string toString();
    // Should never be called by SetRect or aliases functions, this method should call
    // them
    virtual void ComputeLayout(int x, int y);

    EventReceiver* GetEventReceiver() { return &d_eventReceiver; }

    virtual void SetParentEventReceiver(EventReceiver* i_parent) { return; };

   protected:
    SDL_Rect d_rect{0, 0, 0, 0};
    EventReceiver d_eventReceiver;
};
}  // namespace Engine::Layout