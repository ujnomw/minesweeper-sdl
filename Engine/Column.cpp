#include "Column.h"

namespace Engine::Layout
{
void Column::Render(SDL_Surface* i_surface)
{
    for (auto c : d_children) c->Render(i_surface);
};

void Column::ComputeLayout(int i_x, int i_y)
{
    SetXY(i_x, i_y);
    if (d_children.empty()) return;
    auto [X, Y] = GetXY();
    int W = 0;
    int H = 0;

    for (auto c : d_children)
    {
        c->ComputeLayout(X, Y);
        auto [_x, _y, w, h] = c->GetRect();
        if (w < 1 || h < 1)
        {
            std::cout << "[ERROR]" << "Wrong column rect! " << c->toString() << std::endl;
            continue;
        }
        SDL_Rect newRect{X, Y, w, h};
        Y = Y + d_gap + h;
        H += h;
        if (w > W) W = w;
    }
    H += (d_children.size() - 1) * d_gap;
    SetWH(W, H);
};

std::string Column::toString() { return "Column:" + UIElement::toString(); }
}  // namespace Engine::Layout