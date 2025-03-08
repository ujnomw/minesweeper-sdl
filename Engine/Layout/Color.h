#pragma once

#include <SDL.h>

namespace Layout
{

class IColor
{
   public:
    virtual ~IColor() = default;

    virtual void SetColor(SDL_Color i_color) = 0;
    virtual SDL_Color GetColor() const = 0;
};

class Color : public IColor
{
   private:
    SDL_Color d_color{0, 0, 0, 0};

   public:
    Color() {};
    Color(SDL_Color i_color) : d_color{i_color} {};
    void SetColor(SDL_Color i_color) override { d_color = i_color; };
    SDL_Color GetColor() const override { return d_color; };
};
}  // namespace Layout
