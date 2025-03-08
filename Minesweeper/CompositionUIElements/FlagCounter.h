#pragma once

#include "Engine/Image.h"
#include "Engine/Layout/HandleEventStrategy.h"
#include "Engine/Layout/RectangleUnit.h"
#include "Engine/Layout/RenderStrategy.h"
#include "Engine/Text.h"
#include "Globals.h"
#include "memory"

namespace C_UI
{
class FlagCounter : public Layout::RectangleUnitBase
{
   private:
    Engine::Image Image;
    Engine::Text Text;
    int FlagsAvailable{Config::BOMB_COUNT};
    std::unique_ptr<Layout::RenderStrategy<FlagCounter>> d_renderer;
    std::unique_ptr<Layout::HandleEventStrategy<FlagCounter>> d_eventHandler;

   public:
    FlagCounter(int x, int y, int w, int h,
                std::unique_ptr<Layout::RenderStrategy<FlagCounter>> i_renderer,
                std::unique_ptr<Layout::HandleEventStrategy<FlagCounter>> i_eventHandler)
        : Image{x,
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
        SetBox({x, y, w, h});
        SetColor(Layout::Color(Config::FLAG_COUNTER_COLOR));
        d_renderer = std::move(i_renderer);
        d_eventHandler = std::move(i_eventHandler);
    };

    Engine::Text& GetText() { return Text; };
    Engine::Image& GetImage() { return Image; };

    void SetFlagsAvailable(int i_flagAvailable) { FlagsAvailable = i_flagAvailable; };
    int GetFlagsAvailable() const { return FlagsAvailable; };

    void Render(SDL_Surface* i_surface) override
    {
        d_renderer->Render(*this, i_surface);
    };
    void HandleEvent(const SDL_Event& E) override
    {
        d_eventHandler->HandleEvent(*this, E);
    };
};

class FlagCounterRenderStrategy : public Layout::RenderStrategy<FlagCounter>
{
   public:
    void Render(FlagCounter& i_flagCounter, SDL_Surface* i_surface) const override
    {
        auto color = i_flagCounter.GetBGColor().GetColor();
        SDL_FillRect(i_surface, &i_flagCounter.GetBox().GetBoundsRef(),
                     SDL_MapRGB(i_surface->format, color.r, color.g, color.b));
        i_flagCounter.GetText().Render(i_surface);
        i_flagCounter.GetImage().Render(i_surface);
    };
};

class FlagCounterHandleEventStrategy : public Layout::HandleEventStrategy<FlagCounter>
{
   public:
    void HandleEvent(FlagCounter& i_flagCounter, const SDL_Event& E)
    {
        int FlagsAvailable = i_flagCounter.GetFlagsAvailable();
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
        i_flagCounter.SetFlagsAvailable(FlagsAvailable);
        i_flagCounter.GetText().SetText(std::to_string(FlagsAvailable));
    };
};
}  // namespace C_UI