#pragma once

#include <iostream>
#include <vector>

#include "Globals.h"
#include "UIElement.h"

namespace Engine::Layout
{
class Column : public UIElement
{
   private:
    std::vector<UIElement*> d_children;
    int d_gap{Config::PADDING};

   public:
    // TODO: Move args
    template <typename... T>
    Column(T&&... args)
    {
        (d_children.push_back(&args), ...);
    };

    void Render(SDL_Surface* i_surface) override;
    void ComputeLayout(int i_x, int i_y) override;

    std::string toString() override;
};
}  // namespace Engine::Layout