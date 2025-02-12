#pragma

#include <SDL.h>

#include <vector>

#include "Engine/Rectangle.h"

template <typename T>
concept Renderable = requires(T&& t, SDL_Surface* i_surface) {
    { t.Render(i_surface) } -> std::same_as<void>;
};

class Row
{
    using R = Engine::Rectangle;

   public:
    Row() = default;
    Row(std::vector<R*>& i_children)
    {
        for (auto* c : i_children)
        {
            children.push_back(c);
        }
    };
    template <typename... Rects>
    Row(Rects&&... rects) : gap{i_gap}
    {
        (children.push_back(rects), ...);
    }
    void Render(SDL_Surface* i_surface)
    {
        for (auto* c : children)
        {
            c->Render(i_surface);
        }
    };

   private:
    std::vector<R*> children;
    int padding;
    int gap;
};