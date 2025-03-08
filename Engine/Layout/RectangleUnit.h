#pragma once

#include <SDL.h>

#include "Box.h"
#include "Color.h"

namespace Layout
{

class IRectangleUnit
{
   public:
    virtual ~IRectangleUnit() = default;
    virtual void Render(SDL_Surface*) = 0;
    virtual void HandleEvent(const SDL_Event& E) = 0;
    virtual void SetBox(Box i_box) = 0;
    virtual void SetColor(Color i_color) = 0;
    virtual Box GetBox() const = 0;
    virtual Color GetBGColor() const = 0;
};

class RectangleUnitBase : public IRectangleUnit
{
   private:
    Box d_box;
    Color d_backgroundColor;

   public:
    RectangleUnitBase() {};
    void SetBox(Box i_box) override { d_box = i_box; };
    void SetColor(Color i_color) override { d_backgroundColor = i_color; };
    Box GetBox() const override { return d_box; };
    Color GetBGColor() const override { return d_backgroundColor; };
    // virtual void Render(SDL_Surface* i_surface) override = 0;
    // virtual void HandleEvent(const SDL_Event& E) override = 0;
};
}  // namespace Layout
