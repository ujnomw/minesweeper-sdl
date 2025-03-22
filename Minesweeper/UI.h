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
    MinesweeperUI() { Layout.ComputeLayout(Config::PADDING, Config::PADDING); };
    void Render(SDL_Surface* Surface) { Layout.Render(Surface); }

    void HandleEvent(const SDL_Event& E)
    {
        Grid.HandleEvent(E);
        Button.HandleEvent(E);
        Counter.HandleEvent(E);
    }
};