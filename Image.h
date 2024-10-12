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
        d_sourceRectangle.w = ImageSurface->w;
        d_sourceRectangle.h = ImageSurface->h;
        SetDestinationRectangle({0, 0, 600, 300});
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
        SDL_BlitScaled(ImageSurface, &d_sourceRectangle, DestinationSurface, &d_destinationRectangle);
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
    SDL_Rect d_destinationRectangle{0, 0, 0, 0};

    void SetDestinationRectangle(
        SDL_Rect Requested)
    {
        float TargetRatio{d_sourceRectangle.w / static_cast<float>(d_sourceRectangle.h)};
        float RequestedRatio{Requested.w / static_cast<float>(Requested.h)};

        d_destinationRectangle = Requested;

        if (RequestedRatio < TargetRatio)
        {
            // Reduce height
            d_destinationRectangle.h = static_cast<int>(
                Requested.w / TargetRatio);
        }
        else
        {
            // Reduce width as before
            d_destinationRectangle.w = static_cast<int>(
                Requested.h * TargetRatio);
        }

        // Non-functional code for logging
        float AppliedRatio{d_destinationRectangle.w /
                           static_cast<float>(d_destinationRectangle.h)};

        std::cout << "\n[Aspect Ratio] Requested: "
                  << RequestedRatio
                  << ", Target:" << TargetRatio
                  << ", Applied: " << AppliedRatio;
    }
};