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
    d_renderer = SDL_CreateRenderer(SDLWindow, -1,
                                    SDL_RENDERER_ACCELERATED | SDL_TEXTUREACCESS_TARGET);
}

void Window::Render()
{
    SDL_SetRenderDrawColor(d_renderer, Config::BACKGROUND_COLOR.r,
                           Config::BACKGROUND_COLOR.g, Config::BACKGROUND_COLOR.b,
                           Config::BACKGROUND_COLOR.a);
    SDL_RenderClear(d_renderer);
}

void Window::Update() { SDL_UpdateWindowSurface(SDLWindow); }

SDL_Surface *Window::GetSurface() { return SDL_GetWindowSurface(SDLWindow); }
SDL_Renderer *Window::GetRenderer() { return d_renderer; };

void Window::SetWH(int w, int h) { SDL_SetWindowSize(SDLWindow, w, h); }

void Window::HandelEvents(const SDL_Event &i_event)
{
    if (i_event.type == UserEvents::DIFFICULTY_CHANGED)
    {
        GameSettings::UpdateSettings();
        SetWH(GameSettings::WindowWidth(), GameSettings::WindowsHeight());
    }
}

Window::~Window()
{
    SDL_DestroyRenderer(d_renderer);
    SDL_DestroyWindow(SDLWindow);
}

}  // namespace Engine