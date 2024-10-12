#pragma once
#include <string>
#include <iostream>
#include <SDL.h>

class Image
{
public:
    Image(std::string File, SDL_PixelFormat *p_preferredFormat = nullptr)
        : ImageSurface{SDL_LoadBMP(File.c_str())}
    {
        if (!ImageSurface)
        {
            std::cout << "Failed to load image "
                      << File << ":\n  " << SDL_GetError();
        }
        if (p_preferredFormat)
        {
            auto *converted = SDL_ConvertSurface(ImageSurface, p_preferredFormat, 0);
            if (converted)
            {
                SDL_FreeSurface(ImageSurface);
                ImageSurface = converted;
            }
            else
            {
                std::cout << "Error converting surface:" << SDL_GetError();
            }
        }
    }

    void Render(SDL_Surface *DestinationSurface)
    {
        SDL_BlitSurface(ImageSurface, nullptr, DestinationSurface, nullptr);
    }

    ~Image()
    {
        SDL_FreeSurface(ImageSurface);
    }

    Image(const Image &) = delete;
    Image &operator=(const Image &) = delete;

private:
    SDL_Surface *ImageSurface{nullptr};
};