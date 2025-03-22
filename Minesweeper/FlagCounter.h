#pragma once
#include <iostream>
#include <string>

#include "Engine/Image.h"
#include "Engine/Rectangle.h"
#include "Engine/Text.h"
#include "Globals.h"

class FlagCounter : public Engine::Rectangle
{
   public:
    FlagCounter(int x, int y, int w, int h)
        : Rectangle{x, y, w, h, Config::FLAG_COUNTER_COLOR},
          Image{x,
                y,
                Config::FOOTER_HEIGHT - Config::PADDING,
                Config::FOOTER_HEIGHT - Config::PADDING,
                Config::FLAG_IMAGE,
                24},
          Text{x + Config::FOOTER_HEIGHT,
               y,
               w - Config::FOOTER_HEIGHT - 24,
               h,
               std::to_string(Config::BOMB_COUNT),
               {255, 255, 255, 255},
               20}
    {
        fitContentInRect();
    }

    FlagCounter()
        : Image{Config::FOOTER_HEIGHT - Config::PADDING,
                Config::FOOTER_HEIGHT - Config::PADDING, Config::FLAG_IMAGE,
                Config::FLAG_COUNTER_ICON_WIDTH},
          Text{0,
               0,
               Config::FLAG_COUNTER_WIDTH - Config::FOOTER_HEIGHT -
                   Config::FLAG_COUNTER_ICON_WIDTH,
               Config::FOOTER_HEIGHT - Config::PADDING,
               std::to_string(Config::BOMB_COUNT),
               {255, 255, 255, 255},
               20}
    {
        SetWH(Config::FLAG_COUNTER_WIDTH, Config::FOOTER_HEIGHT - Config::PADDING);
        SetColor(Config::FLAG_COUNTER_COLOR);
    }

    void SetRect(SDL_Rect i_rect) override
    {
        Rectangle::SetRect(i_rect);
        std::cout << "counter set rect" << std::endl;
        fitContentInRect();
    }

    void Render(SDL_Surface* Surface) override
    {
        Rectangle::Render(Surface);
        Text.Render(Surface);
        Image.Render(Surface);
    }

    void HandleEvent(const SDL_Event& E)
    {
        if (E.type == UserEvents::FLAG_PLACED)
        {
            --FlagsAvailable;
        }
        else if (E.type == UserEvents::FLAG_CLEARED)
        {
            ++FlagsAvailable;
        }
        else if (E.type == UserEvents::GAME_WON)
        {
            FlagsAvailable = 0;
        }
        else if (E.type == UserEvents::NEW_GAME)
        {
            FlagsAvailable = Config::BOMB_COUNT;
        }
        else
        {
            return;
        }
        Text.SetText(std::to_string(FlagsAvailable));
    }

   private:
    void fitContentInRect()
    {
        std::cout << "Fitting started" << std::endl;
        auto [x, y, w, h] = GetRect();
        Image.SetXY(x, y);

        std::cout << "Fitting for image done" << std::endl;
        Text.SetRect({x + Config::FOOTER_HEIGHT, y,
                      w - Config::FOOTER_HEIGHT - Config::FLAG_COUNTER_ICON_WIDTH, h});
        std::cout << "Fitting ended" << std::endl;
    };

   private:
    Engine::Image Image;
    Engine::Text Text;
    int FlagsAvailable{Config::BOMB_COUNT};
};