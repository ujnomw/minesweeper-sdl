#pragma once
#include <SDL_image.h>

#include <string>

#include "Layout.h"
namespace Engine
{
class Image : public Layout::UIElement
{
   public:
    Image() {};
    Image(int w, int h, const std::string& i_filename, int i_padding = 12)
        : d_padding{i_padding}
    {
        SetWH(w, h);
        ImageSurface = IMG_Load(i_filename.c_str());
#ifdef SHOW_DEBUG_HELPERS
        Utils::CheckSDLError("IMG_Load");
#endif
    }
    Image(int x, int y, int w, int h, const std::string& Filename, int Padding = 12)
        : Destination{x + Padding / 2, y + Padding / 2, w - Padding, h - Padding},
          d_padding{Padding}
    {
        ImageSurface = IMG_Load(Filename.c_str());
#ifdef SHOW_DEBUG_HELPERS
        Utils::CheckSDLError("IMG_Load");
#endif
    }

    void Render(SDL_Surface* Surface) override
    {
        SDL_BlitScaled(ImageSurface, nullptr, Surface, &Destination);
    }

    void SetDestinationRect(SDL_Rect i_rect)
    {
        auto [x, y, w, h] = i_rect;
        Destination = {x + d_padding / 2, y + d_padding / 2, w - d_padding,
                       h - d_padding};
    }

    void SetRect(SDL_Rect i_rect) override
    {
        UIElement::SetRect(i_rect);
        auto [x, y, w, h] = i_rect;
        Destination = {x + d_padding / 2, y + d_padding / 2, w - d_padding,
                       h - d_padding};
    }

    ~Image()
    {
        if (ImageSurface)
        {
            SDL_FreeSurface(ImageSurface);
        }
    }

    Image(const Image&) {}

   private:
    SDL_Surface* ImageSurface{nullptr};
    SDL_Rect Destination{0, 0, 0, 0};
    int d_padding = 12;
};
}  // namespace Engine