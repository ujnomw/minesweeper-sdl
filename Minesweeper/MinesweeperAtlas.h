#pragma once

#include <Globals.h>
#include <SDL.h>

#include <iostream>
#include <memory>

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
    MinesweeperAtlas()
    {
        d_atlasSurface = SDL_CreateRGBSurface(0, W, H, 32, 0, 0, 0, 0);
        int x = 0;
        int y = 0;
        for (int i = 0; i < 8; i++)
        {
            Engine::Text text{0, 0, Config::CELL_SIZE, Config::CELL_SIZE,
                              std::to_string(i + 1)};
            SDL_BlitSurface(text.GetTextSurface(), &text.GetRect(), d_atlasSurface,
                            &NumberRects[i]);
        }
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