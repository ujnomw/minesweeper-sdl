#pragma once

#include "Globals.h"
#include "Grid.h"
#include "Minesweeper/NewGameButton.h"

class MinesweeperUI
{
   public:
    void Render(SDL_Surface* Surface)
    {
        Grid.Render(Surface);
        Button.Render(Surface);
    }

    void HandleEvent(const SDL_Event& E)
    {
        Grid.HandleEvent(E);
        Button.HandleEvent(E);
    }

   private:
    MinesweeperGrid Grid{Config::PADDING, Config::PADDING};
    NewGameButton Button{Config::PADDING, Config::GRID_HEIGHT + Config::PADDING * 2,
                         Config::WINDOW_WIDTH - Config::PADDING * 2,
                         Config::FOOTER_HEIGHT - Config::PADDING};
};