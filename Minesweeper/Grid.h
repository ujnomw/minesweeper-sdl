#pragma once
#include <vector>

#include "../Globals.h"
#include "Cell.h"
#include "Engine/Random.h"

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
        PlaceBombs();
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

   private:
    void PlaceBombs()
    {
        int bombsToPlace{Config::BOMB_COUNT};
        while (bombsToPlace > 0)
        {
            const size_t bombIndex = Engine::Random::Int(0, Children.size() - 1);
            if (Children[bombIndex].PlaceBomb())
            {
                --bombsToPlace;
            }
        }
    }

    std::vector<MinesweeperCell> Children;
};