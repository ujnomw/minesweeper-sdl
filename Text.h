#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include <string>

#include "Rectangle.h"

const std::string FONTS_FOLDER = "assets/fonts/";

class Text
{
   public:
    Text(std::string i_content, int i_size = 25) : d_fontPath{"fonts/Roboto-Medium.ttf"}

    {
        d_font = TTF_OpenFont(d_fontPath.c_str(), i_size);
        if (!d_font)
        {
            std::cout << "Error opening font: " << SDL_GetError();
        }
        createSurface(i_content);
    }

    void Render(SDL_Surface *i_destinationSurface)
    {
        SDL_BlitSurface(d_textSurface, nullptr, i_destinationSurface, nullptr);
    }

    void SetSize(int i_size) { TTF_SetFontSize(d_font, i_size); }

    ~Text()
    {
        if (TTF_WasInit())
        {
            TTF_CloseFont(d_font);
        }
        SDL_FreeSurface(d_textSurface);
    }
    Text(const Text &) = delete;
    Text &operator=(const Text &) = delete;

   private:
    SDL_Surface *d_textSurface{nullptr};
    TTF_Font *d_font{nullptr};
    std::string d_fontPath = "fonts/Roboto-Medium.ttf";

    void createSurface(const std::string &content)
    {
        SDL_Surface *newSurface =
            TTF_RenderUTF8_Blended(d_font, content.c_str(), {255, 255, 255});
        if (newSurface)
        {
            SDL_FreeSurface(d_textSurface);
            d_textSurface = newSurface;
        }
        else
        {
            std::cout << "Error creating text surface: " << SDL_GetError();
        }
    }
};