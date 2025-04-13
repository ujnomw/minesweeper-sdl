#pragma once

#include <iostream>
#include <optional>

enum DifficultyMode
{
    Easy,
    Medium,
    Hard
};

struct GameSettings
{
   private:
    static DifficultyMode d_mode;
    static int d_bombCount;
    static int d_gridColumns;
    static int d_gridRows;
    static int d_gridHeight;
    static int d_gridWidth;
    static int d_windowHeight;
    static int d_windowWidth;

   public:
    GameSettings()
    {
        d_mode = DifficultyMode::Easy;
        d_bombCount = 6;
        d_gridRows = 4;
        d_gridColumns = 8;
        updateGridAndWindow();
    };

    static DifficultyMode GetMode();
    static void SetMode(DifficultyMode i_mode);
    static int BombCount();
    static int GridColumns();
    static int GridRows();
    static int GridHeight();
    static int GridWidth();
    static int WindowsHeight();
    static int WindowWidth();

   private:
    static void updateGridAndWindow();
};