#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

#include "Globals.h"

namespace Engine
{
class Text
{
   public:
    Text() {};
    Text(int x, int y, int w, int h, const std::string& Content,
         SDL_Color Color = {0, 0, 0, 255}, int FontSize = 30)
        : DestinationRect{x, y, w, h}, Color{Color}
    {
        Font = TTF_OpenFont(Config::FONT.c_str(), FontSize);
#ifdef SHOW_DEBUG_HELPERS
        Utils::CheckSDLError("TTF_OpenFont");
#endif
        SetText(Content);
    }

    void SetText(const std::string& Text) { SetText(Text, Color); }

    void SetText(const std::string& Text, SDL_Color NewColor)
    {
        if (TextSurface)
        {
            SDL_FreeSurface(TextSurface);
        }
        Color = NewColor;

        TextSurface = TTF_RenderUTF8_Blended(Font, Text.c_str(), Color);
        updateTextPosition();
    }

    void SetDestinationRect(SDL_Rect i_rect)
    {
        DestinationRect = i_rect;
        updateTextPosition();
    }

    void Render(SDL_Surface* Surface)
    {
        SDL_BlitSurface(TextSurface, nullptr, Surface, &TextPosition);
    }

    ~Text()
    {
        if (Font)
        {
            TTF_CloseFont(Font);
        }
        if (TextSurface)
        {
            SDL_FreeSurface(TextSurface);
        }
    }

   private:
    void updateTextPosition()
    {
        auto [x, y, w, h] = DestinationRect;
        // Horizontally centering
        const int WidthDifference{w - TextSurface->w};
        const int LeftOffset{WidthDifference / 2};

        // Vertically centering
        const int HeightDifference{h - TextSurface->h};
        const int TopOffset{HeightDifference / 2};

        TextPosition = {x + LeftOffset, y + TopOffset, w, h};
    }

   private:
    SDL_Surface* TextSurface{nullptr};
    TTF_Font* Font{nullptr};
    SDL_Rect DestinationRect{0, 0, 0, 0};
    SDL_Rect TextPosition{0, 0, 0, 0};
    SDL_Color Color{0, 0, 0, 255};
};
}  // namespace Engine