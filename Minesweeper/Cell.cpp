#include "Minesweeper/Cell.h"

#include <iostream>

#include "Globals.h"

MinesweeperCell::MinesweeperCell(int x, int y, int w, int h, int Row, int Col)
    : Button{x, y, w, h}, Row{Row}, Col{Col}, BombImage{x, y, w, h, Config::BOMB_PATH} {};

void MinesweeperCell::HandleEvent(const SDL_Event& E)
{
    if (E.type == UserEvents::CELL_CLEARED)
    {
        // TODO
        std::cout << "A Cell Was Cleared\n";
    }
    else if (E.type == UserEvents::BOMB_PLACED)
    {
        // TODO
        std::cout << "A Bomb was Placed\n";
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

bool MinesweeperCell::PlaceBomb()
{
    if (hasBomb) return false;
    hasBomb = true;
    ReportEvent(UserEvents::BOMB_PLACED);
    return true;
}

void MinesweeperCell::HandleLeftClick() { ClearCell(); }

void MinesweeperCell::Render(SDL_Surface* Surface)
{
    Button::Render(Surface);
    if (isCleared && hasBomb)
    {
        BombImage.Render(Surface);
    }

#ifdef SHOW_DEBUG_HELPERS
    else if (hasBomb)
    {
        BombImage.Render(Surface);
    }
#endif
}

bool MinesweeperCell::GetHasBomb() const { return hasBomb; }
