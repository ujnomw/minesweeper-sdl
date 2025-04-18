#pragma once
#include <memory>

#include "Engine/Column.h"
#include "Engine/Row.h"
#include "Engine/UIElement.h"
#include "Minesweeper/DifficultyLabel.h"
#include "Minesweeper/DifficultySwitch.h"
#include "Minesweeper/FlagCounter.h"
#include "Minesweeper/Grid.h"
#include "Minesweeper/NewGameButton.h"

class MinesweeperUI : public Engine::Layout::UIElement

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
    MinesweeperUI();
    void Render(SDL_Surface* Surface);

    void ComputeLayout(int i_x, int i_y);
    void HandleEvent(const SDL_Event& E);
};