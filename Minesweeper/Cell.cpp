#include "Minesweeper/Cell.h"

#include <iostream>

#include "Globals.h"

MinesweeperCell::MinesweeperCell(int x, int y, int w, int h, int Row, int Col)
    : Button{x, y, w, h},
      Row{Row},
      Col{Col},
      BombImage{x, y, w, h, Config::BOMB_PATH},
      Text{
          x, y, w, h, std::to_string(AdjacentBombs), Config::TEXT_COLORS[AdjacentBombs]} {
      };

void MinesweeperCell::HandleEvent(const SDL_Event& E)
{
    if (E.type == UserEvents::CELL_CLEARED)
    {
        handleCellCleared(E.user);
    }
    else if (E.type == UserEvents::BOMB_PLACED)
    {
        handleBombPlaced(E.user);
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
    else if (isCleared && AdjacentBombs > 0)
    {
        Text.Render(Surface);
    }

#ifdef SHOW_DEBUG_HELPERS
    else if (hasBomb)
    {
        BombImage.Render(Surface);
    }
#endif
}

bool MinesweeperCell::GetHasBomb() const { return hasBomb; }

bool MinesweeperCell::isAdjustend(MinesweeperCell* i_other) const
{
    return (this != i_other) && (abs(GetRow() - i_other->GetRow()) <= 1) &&
           (abs(GetCol() - i_other->GetCol()) <= 1);
}

void MinesweeperCell::handleBombPlaced(const SDL_UserEvent& E)
{
    MinesweeperCell* cell{static_cast<MinesweeperCell*>(E.data1)};
    if (isAdjustend(cell))
    {
        ++AdjacentBombs;
        Text.SetText(std::to_string(AdjacentBombs), Config::TEXT_COLORS[AdjacentBombs]);
    }
}

void MinesweeperCell::handleCellCleared(const SDL_UserEvent& E)
{
    MinesweeperCell* cell{static_cast<MinesweeperCell*>(E.data1)};

    if (cell->hasBomb) return;

    if (isAdjustend(cell) && cell->AdjacentBombs == 0)
    {
        ClearCell();
    }
}
