#include "GameSettings.h"

#include "Globals.h"

DifficultyMode GameSettings::d_mode = Easy;
int GameSettings::d_bombCount = 0;
int GameSettings::d_gridColumns = 0;
int GameSettings::d_gridRows = 0;
int GameSettings::d_gridHeight = 0;
int GameSettings::d_gridWidth = 0;
int GameSettings::d_windowHeight = 0;
int GameSettings::d_windowWidth = 0;

DifficultyMode GameSettings::GetMode() { return d_mode; };

int GameSettings::BombCount() { return d_bombCount; };

int GameSettings::GridColumns() { return d_gridColumns; };

int GameSettings::GridRows() { return d_gridRows; };

int GameSettings::GridHeight() { return d_gridHeight; };

int GameSettings::GridWidth() { return d_gridWidth; };

int GameSettings::WindowsHeight() { return d_windowHeight; };

int GameSettings::WindowWidth() { return d_windowWidth; };

void GameSettings::SetMode(DifficultyMode i_mode)
{
    switch (i_mode)
    {
        case DifficultyMode::Easy:
            d_bombCount = 6;
            d_gridRows = 4;
            d_gridColumns = 8;
            updateGridAndWindow();
            break;
        case DifficultyMode::Medium:
            d_bombCount = 12;
            d_gridRows = 8;
            d_gridColumns = 8;
            updateGridAndWindow();
            break;
        case DifficultyMode::Hard:
            d_bombCount = 24;
            d_gridRows = 8;
            d_gridColumns = 16;
            updateGridAndWindow();
            break;
        default:
            break;
    }
};

void GameSettings::updateGridAndWindow()
{
    using namespace Config;
    d_gridHeight = CELL_SIZE * d_gridRows + PADDING * (d_gridRows - 1);
    d_gridWidth = CELL_SIZE * d_gridColumns + PADDING * (d_gridColumns - 1);
    d_windowHeight = d_gridHeight + FOOTER_HEIGHT + PADDING * 2;
    d_windowWidth = d_gridWidth + PADDING * 2;
};