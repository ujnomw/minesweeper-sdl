#include "Window.h"

#include "Globals.h"
#include "Minesweeper/GameSettings.h"
namespace Engine
{
Window::Window()
{
    SDLWindow = SDL_CreateWindow(Config::GAME_NAME.c_str(), SDL_WINDOWPOS_UNDEFINED,
                                 SDL_WINDOWPOS_UNDEFINED, GameSettings::WindowWidth(),
                                 GameSettings::WindowsHeight(), 0);
}

void Window::Render()
{
    SDL_FillRect(GetSurface(), nullptr,
                 SDL_MapRGB(GetSurface()->format, Config::BACKGROUND_COLOR.r,
                            Config::BACKGROUND_COLOR.g, Config::BACKGROUND_COLOR.b));
}

void Window::Update() { SDL_UpdateWindowSurface(SDLWindow); }

SDL_Surface *Window::GetSurface() { return SDL_GetWindowSurface(SDLWindow); }

void Window::SetWH(int w, int h) { SDL_SetWindowSize(SDLWindow, w, h); }

void Window::HandelEvent(const SDL_Event &i_event)
{
    if (i_event.type == UserEvents::DIFFICULTY_CHANGED)
    {
        GameSettings::UpdateSettings();
        SetWH(GameSettings::WindowWidth(), GameSettings::WindowsHeight());
    }
}

Window::~Window() { SDL_DestroyWindow(SDLWindow); }

}  // namespace Engine