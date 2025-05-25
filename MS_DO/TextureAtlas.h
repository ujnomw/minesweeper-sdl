#pragma once

#include <SDL.h>

#include "Globals.h"

namespace Entity
{
struct EntityManager;
}

namespace TextureAtlas
{
const int W = 5 * Config::CELL_SIZE;
const int H = 2 * Config::CELL_SIZE;
const int d_side = Config::CELL_SIZE;

const std::vector<SDL_Rect> NumberRects = {
    {0, 0, Config::CELL_SIZE, Config::CELL_SIZE},
    {Config::CELL_SIZE, 0, Config::CELL_SIZE, Config::CELL_SIZE},
    {Config::CELL_SIZE * 2, 0, Config::CELL_SIZE, Config::CELL_SIZE},
    {Config::CELL_SIZE * 3, 0, Config::CELL_SIZE, Config::CELL_SIZE},
    {0, Config::CELL_SIZE, Config::CELL_SIZE, Config::CELL_SIZE},
    {Config::CELL_SIZE, Config::CELL_SIZE, Config::CELL_SIZE, Config::CELL_SIZE},
    {Config::CELL_SIZE * 2, Config::CELL_SIZE, Config::CELL_SIZE, Config::CELL_SIZE},
    {Config::CELL_SIZE * 3, Config::CELL_SIZE, Config::CELL_SIZE, Config::CELL_SIZE}};
const SDL_Rect FlagRect{Config::CELL_SIZE * 4, 0, Config::CELL_SIZE, Config::CELL_SIZE};
const SDL_Rect BombRect{Config::CELL_SIZE * 4, Config::CELL_SIZE, Config::CELL_SIZE,
                        Config::CELL_SIZE};

extern void initTextureAtlas(Entity::EntityManager& em, SDL_Renderer* p_renderer,
                             SDL_Texture*& p_texture);
}  // namespace TextureAtlas