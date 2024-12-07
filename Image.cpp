#include "Image.h"

Image::Image(const std::string &file, const SourceRect &sourceRect,
             const DestRect &destinationRect, ScallingMode i_scallingMode,
             SDL_PixelFormat *format)
    : d_scallingMode(i_scallingMode), d_preferredFormat(format)
{
    loadFile(file);
    SetSourceRectangle(sourceRect);
    SetDestinationRectangle(destinationRect);
}

Image::Image(const std::string &file, ScallingMode i_scallingMode,
             SDL_PixelFormat *format)
    : d_scallingMode(i_scallingMode), d_preferredFormat(format)
{
    loadFile(file);
    SetSourceRectangle({0, 0, d_imageSurface->w, d_imageSurface->h});
    SetDestinationRectangle(d_appliedSrcRectangle);
}

Image::Image(const std::string &file, const DestRect &destinationRect,
             ScallingMode i_scallingMode, SDL_PixelFormat *format)
    : d_scallingMode(i_scallingMode), d_preferredFormat(format)
{
    loadFile(file);
    SetSourceRectangle({0, 0, d_imageSurface->w, d_imageSurface->h});
    SetDestinationRectangle(destinationRect);
}

Image::Image(const std::string &file, const SourceRect &sourceRect,
             ScallingMode i_scallingMode, SDL_PixelFormat *format)
    : d_scallingMode(i_scallingMode), d_preferredFormat(format)
{
    loadFile(file);
    SetSourceRectangle(sourceRect);
    SetDestinationRectangle(d_appliedSrcRectangle);
}

void Image::Render(SDL_Surface *surface)
{
    if (d_scallingMode == ScallingMode::None)
    {
        SDL_BlitSurface(d_imageSurface, &d_appliedSrcRectangle, surface,
                        &d_appliedDestRectangle);
    }
    else
    {
        SDL_BlitScaled(d_imageSurface, &d_appliedSrcRectangle, surface,
                       &d_appliedDestRectangle);
    }
}

void Image::loadFile(const std::string &file)
{
    if (file == d_File) return;
    SDL_Surface *nextSurface = IMG_Load(file.c_str());
    if (validateSurface(nextSurface, "loading file"))
    {
        SDL_FreeSurface(d_imageSurface);
        d_File = file;
        d_imageSurface = nextSurface;
    }

    if (d_preferredFormat)
    {
        convertSurface();
    }
}

void Image::SetSourceRectangle(const SDL_Rect &rect)
{
    d_requestedSrcRectangle = rect;
    if (validateRectangle(rect, d_imageSurface, "Source Rectangle"))
    {
        d_appliedSrcRectangle = rect;
    }
    else
    {
        d_appliedSrcRectangle = {0, 0, d_imageSurface->w, d_imageSurface->h};
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

void Image::SetFile(const std::string &file)
{
    loadFile(file);
    SetSourceRectangle({0, 0, d_imageSurface->w, d_imageSurface->h});
}

void Image::SetFile(const std::string &file, const SourceRect &sourceRect)
{
    loadFile(file);
    SetSourceRectangle(sourceRect);
}

void Image::SetScallingMode(ScallingMode i_mode)
{
    d_scallingMode = i_mode;
    SetDestinationRectangle(d_appliedSrcRectangle);
}
void Image::SetScallingMode(ScallingMode i_mode, const DestRect &destRect)
{
    d_scallingMode = i_mode;
    SetDestinationRectangle(destRect);
}

void Image::SetPreferredFormat(SDL_PixelFormat *i_format)
{
    d_preferredFormat = i_format;
    convertSurface();
}

// Private methods

void Image::convertSurface()
{
    SDL_Surface *convertedSurface =
        SDL_ConvertSurface(d_imageSurface, d_preferredFormat, 0);

    if (validateSurface(convertedSurface, "convert surface"))
    {
        SDL_FreeSurface(d_imageSurface);
        d_imageSurface = convertedSurface;
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

bool Image::validateSurface(const SDL_Surface *surface, const std::string &context)
{
    if (!surface)
    {
        std::cout << "[ERR]" << context << ": " << SDL_GetError() << '\n';
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

// Destructors

Image::~Image() { SDL_FreeSurface(d_imageSurface); }