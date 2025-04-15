#pragma once

#include <iostream>
#include <string>

enum DifficultyMode
{
    Easy,
    Medium,
    Hard,
    None
};

struct GameSettings
{
   private:
    static DifficultyMode d_mode;
    static DifficultyMode d_nextMode;
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
        d_mode = DifficultyMode::None;
        d_nextMode = DifficultyMode::Medium;
        d_bombCount = 6;
        d_gridRows = 4;
        d_gridColumns = 8;
        updateGridAndWindow();
    };

    static DifficultyMode GetMode();
    static const std::string GetNextMode();
    static void SetNextMode(DifficultyMode i_mode);
    static int BombCount();
    static int GridColumns();
    static int GridRows();
    static int GridHeight();
    static int GridWidth();
    static int WindowsHeight();
    static int WindowWidth();
    static void UpdateSettings();
    static void SwitchNextMode();
    static bool IsModeChanged();

   private:
    static void updateGridAndWindow();
    static const std::string modeToText(DifficultyMode i_mode);
};