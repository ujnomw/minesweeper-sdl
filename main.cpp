#include <iostream>
#include <SDL.h>
#include "Window.h"
#include "UI.h"

int main(int argc, char **argv)
{
    SDL_Init(SDL_INIT_VIDEO);
    Window GameWindow;
    UI GameUI;

    SDL_Event Event;
    bool shouldQuit{false};

    while (!shouldQuit)
    {
        while (SDL_PollEvent(&Event))
        {
            GameUI.HandleEvent(Event);
            if (Event.type == SDL_QUIT)
            {
                shouldQuit = true;
            }
        }
        GameWindow.Render();
        GameUI.Render(GameWindow.GetSurface());
        GameWindow.Update();
    }

    SDL_Quit();
    return 0;
}