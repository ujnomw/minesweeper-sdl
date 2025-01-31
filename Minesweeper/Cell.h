#pragma once
#include "Engine/Button.h"
#include "Engine/Image.h"

class MinesweeperCell : public Engine::Button
{
   public:
    MinesweeperCell(int X, int Y, int W, int H, int Row, int Col);

    void HandleEvent(const SDL_Event& E) override;
    void Render(SDL_Surface* Surface) override;

    bool PlaceBomb();

    [[nodiscard]]
    int GetRow() const
    {
        return Row;
    }

    [[nodiscard]]
    int GetCol() const
    {
        return Col;
    }

    [[nodiscard]]
    bool GetHasBomb() const;

   protected:
    void HandleLeftClick() override;

   private:
    void ClearCell();
    void ReportEvent(uint32_t EventType);
    bool isCleared{false};
    bool hasBomb{false};

   private:
    int Row;
    int Col;
    Engine::Image BombImage;
};