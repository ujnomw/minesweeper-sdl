#pragma once
#include <SDL.h>

namespace Engine
{

class Window
{
   public:
    Window();

    void Render();

    void Update();

    SDL_Surface *GetSurface();

    void SetWH(int w, int h);

    void HandelEvents(const SDL_Event &i_event);

    ~Window();

    Window(const Window &) = delete;
    Window &operator=(const Window &) = delete;

   private:
    SDL_Window *SDLWindow;
};
}  // namespace Engine