#pragma once
#include <SDL.h>

#include "../Globals.h"
#include "Minesweeper/GameSettings.h"

namespace Engine
{

class Window
{
   public:
    Window()
    {
        SDLWindow = SDL_CreateWindow(Config::GAME_NAME.c_str(), SDL_WINDOWPOS_UNDEFINED,
                                     SDL_WINDOWPOS_UNDEFINED, GameSettings::WindowWidth(),
                                     GameSettings::WindowsHeight(), 0);
    }

    void Render()
    {
        SDL_FillRect(GetSurface(), nullptr,
                     SDL_MapRGB(GetSurface()->format, Config::BACKGROUND_COLOR.r,
                                Config::BACKGROUND_COLOR.g, Config::BACKGROUND_COLOR.b));
    }

    void Update() { SDL_UpdateWindowSurface(SDLWindow); }

    SDL_Surface *GetSurface() { return SDL_GetWindowSurface(SDLWindow); }

    void SetWH(int w, int h) { SDL_SetWindowSize(SDLWindow, w, h); }

    ~Window() { SDL_DestroyWindow(SDLWindow); }

    Window(const Window &) = delete;
    Window &operator=(const Window &) = delete;

   private:
    SDL_Window *SDLWindow;
};
}  // namespace Engine