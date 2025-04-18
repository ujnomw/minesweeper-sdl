#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

#include "UIElement.h"

namespace Engine
{
class Text : public Layout::UIElement
{
   public:
    Text() {};
    Text(int x, int y, int w, int h, const std::string& Content,
         SDL_Color Color = {0, 0, 0, 255}, int FontSize = 30);

    void SetText(const std::string& Text);

    void SetText(const std::string& Text, SDL_Color NewColor);

    void Render(SDL_Surface* Surface) override;

    void ComputeLayout(int i_x, int i_y) override;

    ~Text();

   private:
    void updateTextPosition();

   private:
    SDL_Surface* TextSurface{nullptr};
    TTF_Font* Font{nullptr};
    SDL_Rect TextPosition{0, 0, 0, 0};
    SDL_Color Color{0, 0, 0, 255};
};
}  // namespace Engine