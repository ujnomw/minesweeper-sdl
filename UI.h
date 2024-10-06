#pragma once
#include "Button.h"
#include "QuitButton.h"

class UI
{
public:
    void Render(SDL_Surface *Surface)
    {
        MyButton.Render(Surface);
        MyQuitButton.Render(Surface);
    }

    void HandleEvent(const SDL_Event &E)
    {
        MyButton.HandleEvent(E);
        MyQuitButton.HandleEvent(E);
    }

    Button MyButton{50, 50, 50, 50};
    QuitButton MyQuitButton{150, 50, 50, 50};
};