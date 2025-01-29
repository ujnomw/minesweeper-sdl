#include "Minesweeper/Cell.h"

#include <iostream>

#include "Globals.h"

MinesweeperCell::MinesweeperCell(int x, int y, int w, int h, int Row, int Col)
    : Button{x, y, w, h}, Row{Row}, Col{Col} {};

void MinesweeperCell::HandleEvent(const SDL_Event& E)
{
    if (E.type == UserEvents::CELL_CLEARED)
    {
        // TODO
        std::cout << "A Cell Was Cleared\n";
    }
    Button::HandleEvent(E);
}

void MinesweeperCell::ClearCell()
{
    if (isCleared) return;
    isCleared = true;
    SetIsDisabled(true);
    SetColor(Config::BUTTON_CLEARED_COLOR);
    ReportEvent(UserEvents::CELL_CLEARED);
}

void MinesweeperCell::ReportEvent(uint32_t EventType)
{
    SDL_Event event{EventType};
    event.user.data1 = this;
    SDL_PushEvent(&event);
}

void MinesweeperCell::HandleLeftClick() { ClearCell(); }

void MinesweeperCell::Render(SDL_Surface* Surface) { Button::Render(Surface); }