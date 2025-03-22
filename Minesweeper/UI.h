#pragma once

#include "Engine/Layout.h"
#include "Globals.h"
#include "Grid.h"
#include "Minesweeper/FlagCounter.h"
#include "Minesweeper/NewGameButton.h"

class MinesweeperUI

{
   private:
    MinesweeperGrid Grid{Config::PADDING, Config::PADDING};
    NewGameButton Button;
    FlagCounter Counter;
    Engine::Layout::Row Footer{Button, Counter};
    Engine::Layout::Column Layout{Grid, Footer};

   public:
    MinesweeperUI()
    {
        // Footer.SetRect(
        //     {Config::PADDING, Config::GRID_HEIGHT + Config::PADDING * 2, 0, 0});

        // Footer.SetXY(Config::PADDING, Config::GRID_HEIGHT + Config::PADDING * 2);
        Layout.ComputeLayout(Config::PADDING, Config::PADDING);
    };
    void Render(SDL_Surface* Surface)
    {
        // Grid.Render(Surface);
        // Button.Render(Surface);
        // Counter.Render(Surface);
        Layout.Render(Surface);
    }

    void HandleEvent(const SDL_Event& E)
    {
        Grid.HandleEvent(E);
        Button.HandleEvent(E);
        Counter.HandleEvent(E);
    }
};