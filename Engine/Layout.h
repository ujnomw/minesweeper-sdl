#pragma once

#include <SDL.h>

#include <concepts>
#include <iostream>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "Globals.h"

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
    void SetRect(SDL_Rect i_rect) override
    {
        d_rect = i_rect;
        // setBoxesLocation();
    };

    SDL_Rect& GetRect() override { return d_rect; }

    void SetWH(int w, int h)
    {
        auto [x, y, _w, _h] = GetRect();
        SetRect({x, y, w, h});
    };

    void SetXY(int x, int y)
    {
        auto [_x, _y, w, h] = GetRect();
        SetRect({x, y, w, h});
    }

    BoundsPair GetWH()
    {
        auto [_x, _y, w, h] = GetRect();
        return {w, h};
    };

    BoundsPair GetXY()
    {
        auto [x, y, _w, _h] = GetRect();
        return {x, y};
    };

    virtual std::string toString()
    {
        auto [x, y, w, h] = GetRect();
        return std::to_string(x) + '_' + std::to_string(y) + "|" + std::to_string(w) +
               '_' + std::to_string(h);
    }

    // Should never be called by SetRect or aliases functions, this method should call
    // them
    virtual void ComputeLayout(int x, int y)
    {
        SetXY(x, y);
        std::cout << "Base rect " << toString() << std::endl;
    };

   protected:
    SDL_Rect d_rect{0, 0, 0, 0};
};

class Row : public UIElement
{
   private:
    std::vector<UIElement*> d_children;
    int d_gap{Config::PADDING};

   public:
    template <typename... T>
    Row(T&&... args)
    {
        (d_children.push_back(&args), ...);
    };

    void Render(SDL_Surface* i_surface) override
    {
        for (auto c : d_children) c->Render(i_surface);
    };

    void ComputeLayout(int i_x, int i_y) override
    {
        SetXY(i_x, i_y);
        std::cout << "Inside Row rect " << toString() << std::endl;
        if (d_children.empty()) return;
        auto [X, Y] = GetXY();
        int W = 0;
        int H = 0;

        for (auto c : d_children)
        {
            c->ComputeLayout(X, Y);
            auto [_x, _y, w, h] = c->GetRect();
            std::cout << "child rect " << c->toString() << std::endl;
            if (w < 1 || h < 1)
            {
                std::cout << "[ERROR]" << "Wrong rect! " << c->toString() << std::endl;
                continue;
            }
            std::cout << "Valid rect: " << c->toString() << std::endl;
            SDL_Rect newRect{X, Y, w, h};
            X = X + d_gap + w;
            W += w;
            if (h > H) H = h;
        }
        W += (d_children.size() - 1) * d_gap;
        SetWH(W, H);
        std::cout << W << " x " << H << std::endl;
    };

    std::string toString() override { return "Row:" + UIElement::toString(); }
};

class Column : public UIElement
{
   private:
    std::vector<UIElement*> d_children;
    int d_gap{Config::PADDING};

   public:
    template <typename... T>
    Column(T&&... args)
    {
        (d_children.push_back(&args), ...);
    };

    void Render(SDL_Surface* i_surface) override
    {
        for (auto c : d_children) c->Render(i_surface);
    };

    void ComputeLayout(int i_x, int i_y) override
    {
        SetXY(i_x, i_y);
        std::cout << "Inside Column rect " << toString() << std::endl;
        if (d_children.empty()) return;
        auto [X, Y] = GetXY();
        int W = 0;
        int H = 0;

        for (auto c : d_children)
        {
            c->ComputeLayout(X, Y);
            auto [_x, _y, w, h] = c->GetRect();
            std::cout << "child rect " << c->toString() << std::endl;
            if (w < 1 || h < 1)
            {
                std::cout << "[ERROR]" << "Wrong column rect! " << c->toString()
                          << std::endl;
                continue;
            }
            SDL_Rect newRect{X, Y, w, h};
            Y = Y + d_gap + h;
            H += h;
            if (w > W) W = w;
        }
        H += (d_children.size() - 1) * d_gap;
        SetWH(W, H);
        std::cout << W << " x " << H << std::endl;
    };

    std::string toString() override { return "Column:" + UIElement::toString(); }
};
}  // namespace Engine::Layout