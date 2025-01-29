#pragma once
#include <vector>

#include "../Globals.h"
#include "Cell.h"

class MinesweeperGrid
{
   public:
    MinesweeperGrid(int x, int y)
    {
        using namespace Config;
        Children.reserve(GRID_COLUMNS * GRID_ROWS);
        for (int Col{1}; Col <= GRID_COLUMNS; ++Col)
        {
            for (int Row{1}; Row <= GRID_ROWS; ++Row)
            {
                constexpr int Spacing{CELL_SIZE + PADDING};
                Children.emplace_back(x + (Spacing) * (Col - 1),
                                      y + (Spacing) * (Row - 1), CELL_SIZE, CELL_SIZE,
                                      Row, Col);
            }
        }
    }

    void Render(SDL_Surface* Surface)
    {
        for (auto& Child : Children)
        {
            Child.Render(Surface);
        }
    }

    void HandleEvent(const SDL_Event& E)
    {
        for (auto& Child : Children)
        {
            Child.HandleEvent(E);
        }
    }

    std::vector<MinesweeperCell> Children;
};