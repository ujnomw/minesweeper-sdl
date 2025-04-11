#pragma once
#include <vector>

#include "Cell.h"
#include "Engine/Layout.h"
#include "Engine/Random.h"
#include "Globals.h"
#include "Minesweeper/MinesweeperAtlas.h"

class MinesweeperGrid : public Engine::Layout::UIElement
{
   public:
    MinesweeperGrid(int x, int y)
    {
        using namespace Config;
        Children.reserve(GRID_COLUMNS * GRID_ROWS);
        SetWH(GRID_COLUMNS * CELL_SIZE + (GRID_COLUMNS - 1) * PADDING,
              GRID_ROWS * CELL_SIZE + (GRID_ROWS - 1) * PADDING);
        for (int Col{1}; Col <= GRID_COLUMNS; ++Col)
        {
            for (int Row{1}; Row <= GRID_ROWS; ++Row)
            {
                constexpr int Spacing{CELL_SIZE + PADDING};
                Children.emplace_back(x + (Spacing) * (Col - 1),
                                      y + (Spacing) * (Row - 1), CELL_SIZE, CELL_SIZE,
                                      Row, Col, d_atlas);
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
        if (E.type == UserEvents::CELL_CLEARED)
        {
            handleCellCleared(E.user);
        }
        else if (E.type == UserEvents::NEW_GAME)
        {
            for (auto& Child : Children)
            {
                Child.Reset();
            }
            areBombsPlaced = false;
            // PlaceBombs();
        }
        for (auto& Child : Children)
        {
            Child.HandleEvent(E);
        }
    }

   private:
    void PlaceBombs(MinesweeperCell* i_clickedCell)
    {
        int bombsToPlace{Config::BOMB_COUNT};
        cellsToClear = Config::GRID_ROWS * Config::GRID_COLUMNS - Config::BOMB_COUNT;
        while (bombsToPlace > 0)
        {
            const size_t bombIndex = Engine::Random::Int(0, Children.size() - 1);
            const bool isSameCellOrAround =
                i_clickedCell->isAdjustend(&Children[bombIndex]) ||
                i_clickedCell == &Children[bombIndex];
            if (!isSameCellOrAround && Children[bombIndex].PlaceBomb())
            {
                --bombsToPlace;
            }
        }
        areBombsPlaced = true;
    }
    void handleCellCleared(const SDL_UserEvent& E)
    {
        auto* cell{static_cast<MinesweeperCell*>(E.data1)};

        if (!areBombsPlaced)
        {
            PlaceBombs(cell);
        };

        if (cell->GetHasBomb())
        {
            SDL_Event Event{UserEvents::GAME_LOST};
            SDL_PushEvent(&Event);
        }
        else
        {
            --cellsToClear;
            if (cellsToClear == 0)
            {
                SDL_Event Event{UserEvents::GAME_WON};
                SDL_PushEvent(&Event);
            }
        }
    }

    std::vector<MinesweeperCell> Children;
    int cellsToClear;
    bool areBombsPlaced{false};
    MinesweeperAtlas d_atlas;
};