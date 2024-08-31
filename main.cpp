#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
}