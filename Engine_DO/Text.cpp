#include "Engine_DO/Text.h"

#include <iostream>

#include "EntityManager.h"
#include "Globals.h"
namespace Entity
{
void createText(EntityManager& i_em, EntityId i_id, std::string& i_content,
                SDL_Color i_color, int i_fontSize, Size i_size)
{
    i_em.entities[i_id].d_type = "text";
    i_em.entities[i_id].Font = TTF_OpenFont(Config::FONT.c_str(), i_fontSize);
    i_em.entities[i_id].Color = i_color;
    i_em.sizes[i_id] = i_size;
    i_em.entities[i_id].TextSurface =
        TTF_RenderUTF8_Blended(i_em.entities[i_id].Font, i_content.c_str(), i_color);
}

void renderTexts(EntityManager& i_em, SDL_Renderer* i_renderer, EntityIdCollection& i_ids)
{
    auto& entities_em = i_em.entities;
    auto& positions_em = i_em.positions;
    auto& sizes_em = i_em.sizes;
    for (auto& id : i_ids)
    {
        auto& e = entities_em[id];
        auto [x, y] = positions_em[id];
        auto [w, h] = sizes_em[id];
        int surfaceW = e.TextSurface->w;
        int surfaceH = e.TextSurface->h;

        // Horizontally centering
        const int WidthDifference{(int)w - surfaceW};
        const int LeftOffset{WidthDifference / 2};

        // Vertically centering
        const int HeightDifference{(int)h - surfaceH};
        const int TopOffset{HeightDifference / 2};

        SDL_Rect rect{(int)x + LeftOffset, (int)y + TopOffset, surfaceW, surfaceH};

        SDL_Texture* text = SDL_CreateTextureFromSurface(i_renderer, e.TextSurface);
        SDL_RenderCopy(i_renderer, text, NULL, &rect);
        SDL_DestroyTexture(text);
    }
}
}  // namespace Entity