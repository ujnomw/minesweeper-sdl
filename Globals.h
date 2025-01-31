#pragma once

#define SHOW_DEBUG_HELPERS

#include <SDL.h>

#include <iostream>
#include <string>

namespace UserEvents
{
}

namespace Config
{
// Game Settings
inline const std::string GAME_NAME{"Minesweeper"};

inline constexpr int BOMB_COUNT{6};

inline constexpr int GRID_COLUMNS{8};
inline constexpr int GRID_ROWS{4};

static_assert(BOMB_COUNT < GRID_COLUMNS * GRID_ROWS, "Cannot have more bombs than cells");

// Size and Positioning
inline constexpr int PADDING{5};
inline constexpr int CELL_SIZE{50};

inline constexpr int GRID_HEIGHT{CELL_SIZE * GRID_ROWS + PADDING * (GRID_ROWS - 1)};

inline constexpr int GRID_WIDTH{CELL_SIZE * GRID_COLUMNS + PADDING * (GRID_COLUMNS - 1)};

inline constexpr int WINDOW_HEIGHT{GRID_HEIGHT + PADDING * 2};
inline constexpr int WINDOW_WIDTH{GRID_WIDTH + PADDING * 2};

// Colors
inline constexpr SDL_Color BACKGROUND_COLOR{170, 170, 170, 255};
inline constexpr SDL_Color BUTTON_COLOR{200, 200, 200, 255};
inline constexpr SDL_Color BUTTON_HOVER_COLOR{220, 220, 220, 255};
inline constexpr SDL_Color BUTTON_CLEARED_COLOR{240, 240, 240, 255};

// Asset Paths
inline const std::string FONT{"assets/Roboto-Medium.ttf"};
inline const std::string BOMB_PATH{"assets/bomb.png"};
}  // namespace Config

namespace UserEvents
{
inline Uint32 CELL_CLEARED = SDL_RegisterEvents(1);
inline Uint32 BOMB_PLACED = SDL_RegisterEvents(1);
}  // namespace UserEvents

namespace Utils
{
#ifdef SHOW_DEBUG_HELPERS
inline void CheckSDLError(const std::string& Msg)
{
    const char* error = SDL_GetError();
    if (*error != '\0')
    {
        std::cerr << Msg << " Error: " << error << '\n';
        SDL_ClearError();
    }
}
#endif
}  // namespace Utils