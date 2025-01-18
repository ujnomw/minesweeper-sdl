#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <iostream>

#include "Image.h"
#include "Text.h"
#include "UI.h"
#include "Window.h"

int main(int argc, char **argv)
{
    const std::string IMAGE_PATH = "assets/example.png";
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    Window GameWindow;
    const SourceRect Src{0, 0, 200, 200};
    const DestRect Dest{0, 0, GameWindow.GetSurface()->w, GameWindow.GetSurface()->h};
    Image Example{IMAGE_PATH, Src, Dest, ScallingMode::Contain};
    Text TextExample{"Hello world"};
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
        TextExample.Render(GameWindow.GetSurface());
        GameWindow.Update();
    }

    IMG_Quit();
    SDL_Quit();
    TTF_Quit();
    return 0;
}