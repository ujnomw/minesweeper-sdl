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

struct SourceRect : SDL_Rect
{
};
struct DestRect : SDL_Rect
{
};

class Image
{
   public:
    [[nodiscard]]
    int GetWidth()
    {
        return d_imageSurface->w;
    }
    [[nodiscard]]
    int GetHeight()
    {
        return d_imageSurface->h;
    }
    [[nodiscard]]
    ScallingMode GetScalingMode()
    {
        return d_scallingMode;
    }

    Image(const std::string &file, ScallingMode i_scallingMode = ScallingMode::None,
          SDL_PixelFormat *format = nullptr);
    Image(const std::string &file, const SourceRect &sourceRect,
          ScallingMode i_scallingMode = ScallingMode::None,
          SDL_PixelFormat *format = nullptr);
    Image(const std::string &file, const DestRect &destinationRect,
          ScallingMode i_scallingMode = ScallingMode::None,
          SDL_PixelFormat *format = nullptr);
    Image(const std::string &file, const SourceRect &sourceRect,
          const DestRect &destinationRect,
          ScallingMode i_scallingMode = ScallingMode::None,
          SDL_PixelFormat *format = nullptr);
    ~Image();
    void SetSourceRectangle(const SDL_Rect &rect);
    void SetDestinationRectangle(const SDL_Rect &rect);
    void SetFile(const std::string &file);
    void SetFile(const std::string &file, const SourceRect &sourceRect);
    void SetScallingMode(ScallingMode i_mode);
    void SetScallingMode(ScallingMode i_mode, const DestRect &destRect);
    void SetPreferredFormat(SDL_PixelFormat *i_format);
    void Render(SDL_Surface *surface);
    Image(const Image &) = delete;
    Image &operator=(const Image &) = delete;

   private:
    SDL_Surface *d_imageSurface;
    SDL_PixelFormat *d_preferredFormat{nullptr};
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
    bool validateSurface(const SDL_Surface *surface, const std::string &context);
    /**
     * @brief Resizes the source rectangle to ==fill== it with the target
     */
    SDL_Rect matchAspectRatio(const SDL_Rect &source, const SDL_Rect &target);
    void convertSurface();
};