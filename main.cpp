#include <SDL_image.h>
#include <SDL_ttf.h>

#include <chrono>

#include "Engine/Window.h"
#include "Globals.h"
#include "Minesweeper/GameSettings.h"
#include "Minesweeper/UI.h"

int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_VIDEO);
#ifdef SHOW_DEBUG_HELPERS
    Utils::CheckSDLError("SDL_Init");
#endif

    IMG_Init(IMG_INIT_PNG);
#ifdef SHOW_DEBUG_HELPERS
    Utils::CheckSDLError("IMG_Init");
#endif

    TTF_Init();
#ifdef SHOW_DEBUG_HELPERS
    Utils::CheckSDLError("TTF_Init");
#endif
    GameSettings::SetNextMode(DifficultyMode::Hard);
    GameSettings::UpdateSettings();
    Engine::Window GameWindow;
    MinesweeperUI UI;

    SDL_Event Event;
    bool shouldQuit{false};
#ifdef FRAME_PERF_DEBUG
    double totalFrameTime{0};
    int frames{0};
    double averageFrameTime;
#endif

    while (!shouldQuit)
    {
#ifdef FRAME_PERF_DEBUG
        const auto frameStart{std::chrono::steady_clock::now()};
#endif

        while (SDL_PollEvent(&Event))
        {
            if (Event.type == SDL_QUIT)
            {
                shouldQuit = true;
            }
            else
            {
                UI.HandleEvent(Event);
            }
        }
        GameWindow.Render();
        UI.Render(GameWindow.GetSurface());
        GameWindow.Update();
#ifdef FRAME_PERF_DEBUG
        const auto frameEnd{std::chrono::steady_clock::now()};
        const std::chrono::duration<double> elapsed_seconds_frame{frameEnd - frameStart};
        totalFrameTime += elapsed_seconds_frame.count();
        averageFrameTime = totalFrameTime / ++frames;
        std::cout << "AFT ms: " << averageFrameTime * 1000
                  << "; Last frame time ms: " << elapsed_seconds_frame.count() * 1000
                  << std::endl;
#endif
    }
    SDL_Quit();
    return 0;
}