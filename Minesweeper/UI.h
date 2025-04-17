#pragma once
#include <memory>

#include "Engine/Layout.h"
#include "Grid.h"
#include "Minesweeper/DifficultyLabel.h"
#include "Minesweeper/DifficultySwitch.h"
#include "Minesweeper/FlagCounter.h"
#include "Minesweeper/NewGameButton.h"

class MinesweeperUI

{
   private:
    MinesweeperGrid Grid{Config::PADDING, Config::PADDING};
    NewGameButton Button;
    FlagCounter Counter;
    DifficultyLabel Label;
    DifficultySwitch Switch;
    Engine::Layout::Row NewGameRow{Button, Counter};
    Engine::Layout::Row DifficultyRow{Label, Switch};
    std::unique_ptr<Engine::Layout::UIElement> Footer{nullptr};
    std::unique_ptr<Engine::Layout::Column> Layout{nullptr};

   public:
    // TODO: Make simple, once assignment and move constructors are done for layout
    // classes
    MinesweeperUI() { ComputeLayout(Config::PADDING, Config::PADDING); };
    void Render(SDL_Surface* Surface) { Layout->Render(Surface); }

    void ComputeLayout(int i_x, int i_y)
    {
        if (GameSettings::GetMode() == Hard)
        {
            Footer = std::make_unique<Engine::Layout::Row>(NewGameRow, DifficultyRow);
            Layout = std::make_unique<Engine::Layout::Column>(Grid, *Footer.get());
        }
        else
        {
            Layout =
                std::make_unique<Engine::Layout::Column>(Grid, NewGameRow, DifficultyRow);
        }
        Layout->ComputeLayout(i_x, i_y);
    }

    void HandleEvent(const SDL_Event& E)
    {
        if (E.type == UserEvents::DIFFICULTY_CHANGED)
        {
            ComputeLayout(Config::PADDING, Config::PADDING);
            return;
        }
        Grid.HandleEvent(E);
        Button.HandleEvent(E);
        Counter.HandleEvent(E);
        Switch.HandleEvent(E);
        Label.HandleEvent(E);
    }
};