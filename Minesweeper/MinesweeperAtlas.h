#pragma once

#include <SDL.h>

#include "Globals.h"

class MinesweeperAtlas
{
   private:
    const int W = 5 * Config::CELL_SIZE;
    const int H = 2 * Config::CELL_SIZE;
    const int d_side = Config::CELL_SIZE;

   public:
    inline static const std::vector<SDL_Rect> NumberRects = {
        {0, 0, Config::CELL_SIZE, Config::CELL_SIZE},
        {Config::CELL_SIZE, 0, Config::CELL_SIZE, Config::CELL_SIZE},
        {Config::CELL_SIZE * 2, 0, Config::CELL_SIZE, Config::CELL_SIZE},
        {Config::CELL_SIZE * 3, 0, Config::CELL_SIZE, Config::CELL_SIZE},
        {0, Config::CELL_SIZE, Config::CELL_SIZE, Config::CELL_SIZE},
        {Config::CELL_SIZE, Config::CELL_SIZE, Config::CELL_SIZE, Config::CELL_SIZE},
        {Config::CELL_SIZE * 2, Config::CELL_SIZE, Config::CELL_SIZE, Config::CELL_SIZE},
        {Config::CELL_SIZE * 3, Config::CELL_SIZE, Config::CELL_SIZE, Config::CELL_SIZE}};
    inline static const SDL_Rect FlagRect{Config::CELL_SIZE * 4, 0, Config::CELL_SIZE,
                                          Config::CELL_SIZE};
    inline static const SDL_Rect BombRect{Config::CELL_SIZE * 4, Config::CELL_SIZE,
                                          Config::CELL_SIZE, Config::CELL_SIZE};
    MinesweeperAtlas();

    SDL_Surface* GetAtlasSurface();

    ~MinesweeperAtlas();

   private:
    SDL_Surface* d_atlasSurface{nullptr};
};