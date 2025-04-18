#include "Image.h"

namespace Engine
{
Image::Image(int w, int h, const std::string& i_filename, int i_padding)
    : d_padding{i_padding}
{
    SetWH(w, h);
    ImageSurface = IMG_Load(i_filename.c_str());
#ifdef SHOW_DEBUG_HELPERS
    Utils::CheckSDLError("IMG_Load");
#endif
}
Image::Image(int x, int y, int w, int h, const std::string& Filename, int Padding)
    : d_padding{Padding}
{
    SetRect({x, y, w, h});
    updateDestinationRect();
    ImageSurface = IMG_Load(Filename.c_str());
#ifdef SHOW_DEBUG_HELPERS
    Utils::CheckSDLError("IMG_Load");
#endif
}

void Image::Render(SDL_Surface* Surface)
{
    SDL_BlitScaled(ImageSurface, nullptr, Surface, &Destination);
}

void Image::ComputeLayout(int i_x, int i_y)
{
    SetXY(i_x, i_y);
    updateDestinationRect();
}

Image::~Image()
{
    if (ImageSurface)
    {
        SDL_FreeSurface(ImageSurface);
    }
}

Image::Image(const Image&) {}

void Image::updateDestinationRect()
{
    auto [x, y, w, h] = GetRect();
    Destination = {x + d_padding / 2, y + d_padding / 2, w - d_padding, h - d_padding};
}
}  // namespace Engine