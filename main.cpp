#include <iostream>
#include <SDL.h>
#include "Window.h"
#include "UI.h"
#include "Image.h"

int main(int argc, char **argv)
{
    const std::string IMAGE_PATH = "assets/example.bmp";
    SDL_Init(SDL_INIT_VIDEO);
    Window GameWindow;
    Image Example{IMAGE_PATH, GameWindow.GetSurface()->format};
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
        Example.Render(GameWindow.GetSurface());
        GameWindow.Update();
    }

    SDL_Quit();
    return 0;
}