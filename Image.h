#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <string>

enum class ScallingMode
{
    None,
    Fill,
    Contain
};

class Image
{
   public:
    Image(const std::string &file, const SDL_Rect &sourceRect,
          const SDL_Rect &destinationRect, ScallingMode i_scallingMode);
    void Render(SDL_Surface *surface);
    ~Image();
    void SetSourceRectangle(const SDL_Rect &rect);
    void SetDestinationRectangle(const SDL_Rect &rect);
    Image(const Image &) = delete;
    Image &operator=(const Image &) = delete;

   private:
    SDL_Surface *d_ImageSurface;
    SDL_Rect d_appliedSrcRectangle;
    SDL_Rect d_requestedSrcRectangle;
    SDL_Rect d_appliedDestRectangle;
    SDL_Rect d_requestedDestRectangle;
    ScallingMode d_scallingMode;
    std::string d_File;

    void loadFile(const std::string &file);
    bool rectangleWithinSurface(const SDL_Rect &rect, const SDL_Surface *surface) const;
    bool validateRectangle(const SDL_Rect &rect, const SDL_Surface *surface,
                           const std::string &context) const;
    SDL_Rect matchAspectRatio(const SDL_Rect &source, const SDL_Rect &target);
};