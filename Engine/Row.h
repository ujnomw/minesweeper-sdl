#pragma

#include <SDL.h>

#include <vector>

template <typename T>
concept Renderable = requires(T&& t, SDL_Surface* i_surface) {
    { t.Render(i_surface) } -> std::same_as<void>;
};

template <Renderable R>
class Row
{
   public:
    Row() = default;
    Row(std::vector<R*>& i_children)
    {
        for (auto* c : i_children)
        {
            children.push_back(c);
        }
    };
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