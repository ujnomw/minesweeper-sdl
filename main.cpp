#include <SDL_image.h>
#include <SDL_ttf.h>

#include <chrono>
#include <memory>

#include "Engine/Window.h"
#include "Engine_DO/EntityManager.h"
#include "Engine_DO/TTFManager.h"
#include "Engine_DO/World.h"
#include "Engine_DO/WorldImpl.h"
#include "Globals.h"
#include "MS_DO/GameLoop.h"
#include "MS_DO/TextureAtlas.h"
#include "Minesweeper/GameSettings.h"
#include "Minesweeper/UI.h"

int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_VIDEO);
#ifdef SHOW_DEBUG_HELPERS
    Utils::CheckSDLError("SDL_Init");
#endif
    FontSystem::TTFManager ttf;
#ifdef SHOW_DEBUG_HELPERS
    Utils::CheckSDLError("TTF_Init");
#endif

    IMG_Init(IMG_INIT_PNG);
#ifdef SHOW_DEBUG_HELPERS
    Utils::CheckSDLError("IMG_Init");
#endif

    GameSettings::SetNextMode(DifficultyMode::Hard);
    GameSettings::UpdateSettings();
    Engine::Window GameWindow;
    // MinesweeperUI UI;

    std::unique_ptr<Entity::EntityManager> em =
        std::unique_ptr<Entity::EntityManager>(Entity::createManager(23));
    TextureAtlas::initTextureAtlas(*em.get(), GameWindow.GetRenderer(), em->atlas);
    GameLoop::init(em.get());
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
                // GameWindow.HandelEvents(Event);
                // UI.HandleEvent(Event);
            }
        }
        GameWindow.Render();
        // UI.Render(GameWindow.GetSurface());
        GameLoop::render(*em.get(), GameWindow.GetRenderer());
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
    // TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return 0;
}