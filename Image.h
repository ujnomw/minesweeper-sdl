#pragma once
#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

class Image
{
public:
    Image(std::string File, SDL_PixelFormat *p_preferredFormat = nullptr)
        : ImageSurface{IMG_Load(File.c_str())}
    {
        if (!ImageSurface)
        {
            std::cout << "Failed to load image "
                      << File << ":\n  " << SDL_GetError();
        }
    }

    void Render(SDL_Surface *DestinationSurface)
    {
        SDL_BlitScaled(ImageSurface, nullptr, DestinationSurface, &d_destinationRectangle);
    }

    ~Image()
    {
        SDL_FreeSurface(ImageSurface);
    }

    Image(const Image &) = delete;
    Image &operator=(const Image &) = delete;

private:
    SDL_Surface *ImageSurface;
    SDL_Rect d_sourceRectangle{0, 0, 0, 0};
    SDL_Rect d_destinationRectangle{200, 50, 200, 200};
};