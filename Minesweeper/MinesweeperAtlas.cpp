#include "MinesweeperAtlas.h"

#include "Engine/Image.h"
#include "Engine/Text.h"

MinesweeperAtlas::MinesweeperAtlas()
{
    d_atlasSurface =
        SDL_CreateRGBSurface(0, W, H, 32, 0xff, 0xff00, 0xff0000, 0xff000000);
    for (int i = 0; i < 8; i++)
    {
        auto rect = NumberRects[i];
        auto [x, y, w, h] = rect;
        Engine::Text text{x, y, w, h, std::to_string(i + 1), Config::TEXT_COLORS[i + 1]};
        text.Render(d_atlasSurface);
    }
    Engine::Image bombImage{BombRect.x, BombRect.y, BombRect.w, BombRect.h,
                            Config::BOMB_PATH};
    Engine::Image flagImage{FlagRect.x, FlagRect.y, FlagRect.w, FlagRect.h,
                            Config::FLAG_IMAGE};
    bombImage.Render(d_atlasSurface);
    flagImage.Render(d_atlasSurface);
}

SDL_Surface* MinesweeperAtlas::GetAtlasSurface() { return d_atlasSurface; }

MinesweeperAtlas::~MinesweeperAtlas()
{
    if (d_atlasSurface != nullptr)
    {
        SDL_FreeSurface(d_atlasSurface);
    }
}
