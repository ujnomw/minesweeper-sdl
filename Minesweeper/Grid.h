#pragma once
#include <vector>

#include "Cell.h"
#include "Engine/Layout.h"
#include "Engine/Random.h"
#include "Globals.h"
#include "Minesweeper/GameSettings.h"
#include "Minesweeper/MinesweeperAtlas.h"

class MinesweeperGrid : public Engine::Layout::UIElement
{
   public:
    MinesweeperGrid(int x, int y) { SetXY(x, y); }

    void ComputeLayout(int x, int y) override
    {
        using namespace Config;
        if (Children.size() > 0)
        {
            Children.clear();
        }
        const int columns = GameSettings::GridColumns();
        const int rows = GameSettings::GridRows();
        Children.reserve(columns * rows);
        SetWH(columns * CELL_SIZE + (columns - 1) * PADDING,
              rows * CELL_SIZE + (rows - 1) * PADDING);
        for (int Col{1}; Col <= columns; ++Col)
        {
            for (int Row{1}; Row <= rows; ++Row)
            {
                constexpr int Spacing{CELL_SIZE + PADDING};
                Children.emplace_back(x + (Spacing) * (Col - 1),
                                      y + (Spacing) * (Row - 1), CELL_SIZE, CELL_SIZE,
                                      Row, Col, d_atlas);
            }
        }
    }

    void Render(SDL_Surface* Surface) override
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
            return;
        }
        for (auto& Child : Children)
        {
            Child.HandleEvent(E);
        }
    }

   private:
    void PlaceBombs(MinesweeperCell* i_clickedCell)
    {
        int bombsToPlace{GameSettings::BombCount()};
        const int columns = GameSettings::GridColumns();
        const int rows = GameSettings::GridRows();
        cellsToClear = rows * columns - GameSettings::BombCount();
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