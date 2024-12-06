#include "Image.h"

Image::Image(const std::string &file, const SDL_Rect &sourceRect,
             const SDL_Rect &destinationRect, ScallingMode i_scallingMode)
    : d_scallingMode(i_scallingMode)
{
    loadFile(file);
    SetSourceRectangle(sourceRect);
    SetDestinationRectangle(destinationRect);
}

void Image::Render(SDL_Surface *surface)
{
    if (d_scallingMode == ScallingMode::None)
    {
        SDL_BlitSurface(d_ImageSurface, &d_appliedSrcRectangle, surface,
                        &d_appliedDestRectangle);
    }
    else
    {
        SDL_BlitScaled(d_ImageSurface, &d_appliedSrcRectangle, surface,
                       &d_appliedDestRectangle);
    }
}

void Image::loadFile(const std::string &file)
{
    if (file == d_File)
    {
        return;
    }
    SDL_FreeSurface(d_ImageSurface);
    d_File = file;
    d_ImageSurface = IMG_Load(file.c_str());
}

void Image::SetSourceRectangle(const SDL_Rect &rect)
{
    d_requestedSrcRectangle = rect;
    if (validateRectangle(rect, d_ImageSurface, "Source Rectangle"))
    {
        d_appliedSrcRectangle = rect;
    }
    else
    {
        d_appliedSrcRectangle = {0, 0, d_ImageSurface->w, d_ImageSurface->h};
    }
}

void Image::SetDestinationRectangle(const SDL_Rect &rect)
{
    d_requestedDestRectangle = rect;
    if (validateRectangle(rect, nullptr, "Destination Rectangle"))
    {
        d_appliedDestRectangle = d_scallingMode == ScallingMode::Contain
                                     ? matchAspectRatio(rect, d_appliedSrcRectangle)
                                     : rect;
    }
    else
    {
        d_appliedDestRectangle = {0, 0, d_appliedSrcRectangle.w, d_appliedSrcRectangle.h};
    }
}

bool Image::rectangleWithinSurface(const SDL_Rect &rect, const SDL_Surface *surface) const
{
    if (rect.x + rect.w > surface->w) return false;
    if (rect.y + rect.h > surface->h) return false;
    if (rect.x < 0) return false;
    if (rect.y < 0) return false;
    return true;
}

bool Image::validateRectangle(const SDL_Rect &rect, const SDL_Surface *surface,
                              const std::string &context) const
{
    if (SDL_RectEmpty(&rect))
    {
        std::cout << "[ERR] Rect " << context << "has no area" << std::endl;
        return false;
    }
    if (surface && !rectangleWithinSurface(rect, surface))
    {
        std::cout << "[ERR] Rect " << context << "is out of surface" << std::endl;
        return false;
    }
    return true;
}

SDL_Rect Image::matchAspectRatio(const SDL_Rect &source, const SDL_Rect &target)
{
    // The aspect of the rect INSIDE WHICH we will render
    float sourceRatio{source.w / static_cast<float>(source.h)};
    // The aspect ratio of existing image we would like to achieve
    float targetRatio{target.w / static_cast<float>(target.h)};

    SDL_Rect result = source;

    if (sourceRatio < targetRatio)
    {
        result.h = static_cast<int>(source.w / targetRatio);
    }
    else
    {
        result.w = static_cast<int>(source.h * targetRatio);
    }

    return result;
}

Image::~Image() { SDL_FreeSurface(d_ImageSurface); }