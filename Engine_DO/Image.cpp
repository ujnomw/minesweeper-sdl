#include "Engine_DO/Image.h"

#include <SDL_image.h>

#include "EntityManager.h"

namespace Entity
{
void createImage(EntityManager& em, EntityId i_id, const std::string& i_filename)
{
    int index = em.idsToIndexes[i_id];
    em.entities[index].d_type = "image";
    em.entities[index].ImageSurface = IMG_Load(i_filename.c_str());
};
void renderImages(EntityManager& i_em, SDL_Renderer* i_renderer,
                  EntityIdCollection& i_ids)
{
    auto& entities_em = i_em.entities;
    auto& positions_em = i_em.positions;
    auto& sizes_em = i_em.sizes;
    auto& idsToIndexes_em = i_em.idsToIndexes;
    for (auto& id : i_ids)
    {
        int index = idsToIndexes_em[id];
        auto& entity = entities_em[index];
        int surfaceW = entity.ImageSurface->w;
        int surfaceH = entity.ImageSurface->h;
        auto [x, y] = positions_em[index];
        auto [w, h] = sizes_em[index];
        // Horizontally centering
        const int WidthDifference{(int)w - surfaceW};
        const int LeftOffset{WidthDifference / 2};

        // Vertically centering
        const int HeightDifference{(int)h - surfaceH};
        const int TopOffset{HeightDifference / 2};

        SDL_Rect rect{(int)x + LeftOffset, (int)y + TopOffset, surfaceW, surfaceH};

        SDL_Texture* image =
            SDL_CreateTextureFromSurface(i_renderer, entity.ImageSurface);
        SDL_RenderCopy(i_renderer, image, NULL, &rect);
        SDL_DestroyTexture(image);
    }
};
}  // namespace Entity