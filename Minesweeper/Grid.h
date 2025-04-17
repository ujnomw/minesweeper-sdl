#pragma once
#include <vector>

#include "Cell.h"
#include "Engine/Layout.h"
#include "MinesweeperAtlas.h"

class MinesweeperCell;
class MinesweeperGrid : public Engine::Layout::UIElement
{
   public:
    MinesweeperGrid(int x, int y);

    void ComputeLayout(int x, int y) override;

    void Render(SDL_Surface* Surface) override;
    void HandleEvent(const SDL_Event& E);

   private:
    void PlaceBombs(MinesweeperCell* i_clickedCell);
    void handleCellCleared(const SDL_UserEvent& E);

    std::vector<MinesweeperCell> Children;
    int cellsToClear;
    bool areBombsPlaced{false};
    MinesweeperAtlas d_atlas;
};