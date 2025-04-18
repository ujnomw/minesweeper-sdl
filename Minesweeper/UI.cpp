#include "Minesweeper/UI.h"

MinesweeperUI::MinesweeperUI()
{
    ComputeLayout(Config::PADDING, Config::PADDING);
    Grid.SetParentEventReceiver(&d_eventReceiver);
};
void MinesweeperUI::Render(SDL_Surface* Surface) { Layout->Render(Surface); }

// TODO: Make simple, once assignment and move constructors are done for layout
// classes
void MinesweeperUI::ComputeLayout(int i_x, int i_y)
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

void MinesweeperUI::HandleEvent(const SDL_Event& E)
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