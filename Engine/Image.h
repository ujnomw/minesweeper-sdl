#pragma once
#include <SDL_image.h>

#include <string>

#include "UIElement.h"
namespace Engine
{
class Image : public Layout::UIElement
{
   public:
    Image() {};
    Image(int w, int h, const std::string& i_filename, int i_padding = 12);
    Image(int x, int y, int w, int h, const std::string& Filename, int Padding = 12);

    void Render(SDL_Surface* Surface) override;
    void ComputeLayout(int i_x, int i_y) override;

    ~Image();
    Image(const Image&);

   private:
    void updateDestinationRect();

   private:
    SDL_Surface* ImageSurface{nullptr};
    SDL_Rect Destination{0, 0, 0, 0};
    int d_padding = 12;
};
}  // namespace Engine