#include "UIElement.h"

namespace Engine::Layout
{
void UIElement::SetRect(SDL_Rect i_rect) { d_rect = i_rect; };

SDL_Rect& UIElement::GetRect() { return d_rect; }

void UIElement::SetWH(int w, int h)
{
    auto [x, y, _w, _h] = GetRect();
    SetRect({x, y, w, h});
};

void UIElement::SetXY(int x, int y)
{
    auto [_x, _y, w, h] = GetRect();
    SetRect({x, y, w, h});
}

BoundsPair UIElement::GetWH()
{
    auto [_x, _y, w, h] = GetRect();
    return {w, h};
};

BoundsPair UIElement::GetXY()
{
    auto [x, y, _w, _h] = GetRect();
    return {x, y};
};

std::string UIElement::toString()
{
    auto [x, y, w, h] = GetRect();
    return std::to_string(x) + '_' + std::to_string(y) + "|" + std::to_string(w) + '_' +
           std::to_string(h);
}

// Should never be called by SetRect or aliases functions, this method should call
// them
void UIElement::ComputeLayout(int x, int y) { SetXY(x, y); };
}  // namespace Engine::Layout