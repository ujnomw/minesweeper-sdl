#pragma once

#include <SDL.h>

// struct Bounds
// {
//     int d_w{0};
//     int d_h{0};
//     int d_x{0};
//     int d_y{0};
// };

using Bounds = SDL_Rect;

class IBox
{
   public:
    // virtual void Render(SDL_Surface *) = 0;
    virtual Bounds GetBounds() const = 0;
    virtual Bounds& GetBoundsRef() = 0;
    virtual void SetBounds(const Bounds&) = 0;
    virtual bool IsWithinBounds(int x, int y) const = 0;
    virtual ~IBox() = default;
};

class Box : public IBox
{
   private:
    Bounds d_bounds{0, 0, 0, 0};

   public:
    Box(int x, int y, int w, int h) : d_bounds{x, y, w, h} {};
    Bounds& GetBoundsRef() override { return d_bounds; };
    Bounds GetBounds() const override { return d_bounds; };
    void SetBounds(const Bounds& i_bounds) override { d_bounds = i_bounds; };
    bool IsWithinBounds(int x, int y) const override
    {
        // Too far left
        if (x < d_bounds.x) return false;
        // Too far right
        if (x > d_bounds.x + d_bounds.w) return false;
        // Too high
        if (y < d_bounds.y) return false;
        // Too low
        if (y > d_bounds.y + d_bounds.h) return false;
        // Within bounds
        return true;
    };
};
