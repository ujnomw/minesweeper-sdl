#pragma once
#include <memory>

#include "Engine/Layout.h"
#include "Globals.h"
#include "Grid.h"
#include "Minesweeper/DifficultyLabel.h"
#include "Minesweeper/FlagCounter.h"
#include "Minesweeper/NewGameButton.h"

class MinesweeperUI

{
   private:
    MinesweeperGrid Grid{Config::PADDING, Config::PADDING};
    NewGameButton Button;
    FlagCounter Counter;
    DifficultyLabel Label;

    Engine::Layout::Row Footer{Button, Counter};
    std::unique_ptr<Engine::Layout::UIElement> Footer_{nullptr};
    std::unique_ptr<Engine::Layout::Column> Layout{nullptr};

   public:
    // TODO: Make simple, once assignment and move constructors are done for layout
    // classes
    MinesweeperUI()
    {
        if (GameSettings::GetMode() == Hard)
        {
            Footer_ = std::make_unique<Engine::Layout::Row>(Button, Counter, Label);
            Layout = std::make_unique<Engine::Layout::Column>(Grid, *Footer_.get());
        }
        else
        {
            Footer_ = std::make_unique<Engine::Layout::Row>(Button, Counter);
            Layout =
                std::make_unique<Engine::Layout::Column>(Grid, *Footer_.get(), Label);
        }
        Layout->ComputeLayout(Config::PADDING, Config::PADDING);
    };
    void Render(SDL_Surface* Surface) { Layout->Render(Surface); }

    void HandleEvent(const SDL_Event& E)
    {
        Grid.HandleEvent(E);
        Button.HandleEvent(E);
        Counter.HandleEvent(E);
    }
};