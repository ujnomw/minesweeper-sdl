#include "Minesweeper/Cell.h"

#include <iostream>

#include "Globals.h"

MinesweeperCell::MinesweeperCell(int x, int y, int w, int h, int Row, int Col)
    : Button{x, y, w, h},
      Row{Row},
      Col{Col},
      BombImage{x, y, w, h, Config::BOMB_PATH},
      FlagImage{x, y, w, h, Config::FLAG_IMAGE},
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
    else if (E.type == UserEvents::GAME_WON)
    {
        if (hasBomb)
        {
            hasFlag = true;
            SetColor(Config::BUTTON_SUCCESS_COLOR);
        }
        SetIsDisabled(true);
    }
    else if (E.type == UserEvents::GAME_LOST)
    {
        if (hasBomb)
        {
            isCleared = true;
            SetColor(Config::BUTTON_FAILURE_COLOR);
        }
        SetIsDisabled(true);
    }
    Button::HandleEvent(E);
}

void MinesweeperCell::ClearCell()
{
    if (isCleared || hasFlag) return;
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

void MinesweeperCell::HandleLeftClick()
{
    if (!hasFlag) ClearCell();
}

void MinesweeperCell::Render(SDL_Surface* Surface)
{
    Button::Render(Surface);
    if (hasFlag)
    {
        FlagImage.Render(Surface);
    }
    else if (isCleared && hasBomb)
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
    auto* cell{static_cast<MinesweeperCell*>(E.data1)};

    if (cell->hasBomb) return;

    if (isAdjustend(cell) && cell->AdjacentBombs == 0)
    {
        ClearCell();
    }
}

void MinesweeperCell::Reset()
{
    isCleared = false;
    hasFlag = false;
    hasBomb = false;
    AdjacentBombs = 0;
    SetIsDisabled(false);
    SetColor(Config::BUTTON_COLOR);
}

void MinesweeperCell::HandleRightClick()
{
    if (hasFlag)
    {
        ReportEvent(UserEvents::FLAG_CLEARED);
        hasFlag = false;
    }
    else
    {
        ReportEvent(UserEvents::FLAG_PLACED);
        hasFlag = true;
    }
}