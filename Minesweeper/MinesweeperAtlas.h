#pragma once

#include <Globals.h>
#include <SDL.h>

#include <memory>

#include "Engine/Image.h"
#include "Engine/Text.h"

class MinesweeperAtlas
{
   private:
    const int W = 5 * Config::CELL_SIZE;
    const int H = 2 * Config::CELL_SIZE;
    const int d_side = Config::CELL_SIZE;

   public:
    inline static std::vector<SDL_Rect> NumberRects = {
        {0, 0, Config::CELL_SIZE, Config::CELL_SIZE},
        {Config::CELL_SIZE, 0, Config::CELL_SIZE, Config::CELL_SIZE},
        {Config::CELL_SIZE * 2, 0, Config::CELL_SIZE, Config::CELL_SIZE},
        {Config::CELL_SIZE * 3, 0, Config::CELL_SIZE, Config::CELL_SIZE},
        {0, Config::CELL_SIZE, Config::CELL_SIZE, Config::CELL_SIZE},
        {Config::CELL_SIZE, Config::CELL_SIZE, Config::CELL_SIZE, Config::CELL_SIZE},
        {Config::CELL_SIZE * 2, Config::CELL_SIZE, Config::CELL_SIZE, Config::CELL_SIZE},
        {Config::CELL_SIZE * 3, Config::CELL_SIZE, Config::CELL_SIZE, Config::CELL_SIZE}};
    inline static SDL_Rect FlagRect{Config::CELL_SIZE * 4, 0, Config::CELL_SIZE,
                                    Config::CELL_SIZE};
    inline static SDL_Rect BombRect{Config::CELL_SIZE * 4, Config::CELL_SIZE,
                                    Config::CELL_SIZE, Config::CELL_SIZE};
    MinesweeperAtlas()
    {
        d_atlasSurface =
            SDL_CreateRGBSurface(0, W, H, 32, 0xff, 0xff00, 0xff0000, 0xff000000);
        for (int i = 0; i < 8; i++)
        {
            auto rect = NumberRects[i];
            auto [x, y, w, h] = rect;
            Engine::Text text{
                x, y, w, h, std::to_string(i + 1), Config::TEXT_COLORS[i + 1]};
            text.Render(d_atlasSurface);
        }
        Engine::Image bombImage{BombRect.x, BombRect.y, BombRect.w, BombRect.h,
                                Config::BOMB_PATH};
        Engine::Image flagImage{FlagRect.x, FlagRect.y, FlagRect.w, FlagRect.h,
                                Config::FLAG_IMAGE};
        bombImage.Render(d_atlasSurface);
        flagImage.Render(d_atlasSurface);
    }

    SDL_Surface* GetAtlasSurface() { return d_atlasSurface; }

    ~MinesweeperAtlas()
    {
        if (d_atlasSurface != nullptr)
        {
            SDL_FreeSurface(d_atlasSurface);
        }
    }

   private:
    SDL_Surface* d_atlasSurface{nullptr};
};