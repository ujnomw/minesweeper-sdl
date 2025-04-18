#include "Text.h"

#include "Globals.h"
namespace Engine
{
Text::Text(int x, int y, int w, int h, const std::string& Content, SDL_Color Color,
           int FontSize)
    : Color{Color}
{
    SetRect({x, y, w, h});
    Font = TTF_OpenFont(Config::FONT.c_str(), FontSize);
#ifdef SHOW_DEBUG_HELPERS
    Utils::CheckSDLError("TTF_OpenFont");
#endif
    SetText(Content);
}

void Text::SetText(const std::string& Text) { SetText(Text, Color); }

void Text::SetText(const std::string& Text, SDL_Color NewColor)
{
    if (TextSurface)
    {
        SDL_FreeSurface(TextSurface);
    }
    Color = NewColor;

    TextSurface = TTF_RenderUTF8_Blended(Font, Text.c_str(), Color);
    updateTextPosition();
}

void Text::Render(SDL_Surface* Surface)
{
    SDL_BlitSurface(TextSurface, nullptr, Surface, &TextPosition);
}

void Text::ComputeLayout(int i_x, int i_y)
{
    SetXY(i_x, i_y);
    updateTextPosition();
}

Text::~Text()
{
    if (Font)
    {
        TTF_CloseFont(Font);
    }
    if (TextSurface)
    {
        SDL_FreeSurface(TextSurface);
    }
}

void Text::updateTextPosition()
{
    if (TextSurface == nullptr)
    {
        return;
    }
    auto [x, y, w, h] = GetRect();
    // Horizontally centering
    const int WidthDifference{w - TextSurface->w};
    const int LeftOffset{WidthDifference / 2};

    // Vertically centering
    const int HeightDifference{h - TextSurface->h};
    const int TopOffset{HeightDifference / 2};

    TextPosition = {x + LeftOffset, y + TopOffset, w, h};
}

}  // namespace Engine