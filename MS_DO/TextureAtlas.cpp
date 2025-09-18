#include "TextureAtlas.h"

#include "Engine_DO/EntityManager.h"
#include "Engine_DO/Image.h"
#include "Engine_DO/Text.h"
namespace TextureAtlas
{
void initTextureAtlas(Entity::EntityManager& i_em, SDL_Renderer* p_renderer,
                      SDL_Texture*& p_texture)
{
    using namespace Entity;
    p_texture = SDL_CreateTexture(p_renderer, SDL_PIXELFORMAT_RGBA8888,
                                  SDL_TEXTUREACCESS_TARGET, W, H);
    SDL_SetTextureBlendMode(p_texture, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(p_renderer, p_texture);

    auto& entities_em = i_em.entities;
    auto& positions_em = i_em.positions;
    auto& sizes_em = i_em.sizes;
    auto& idsToIndexes_em = i_em.idsToIndexes;
    EntityIdCollection texts;
    EntityIdCollection images;
    std::vector<Position> textPositions;
    std::vector<Size> textSizes;
    // Create texts
    createEntities(entities_em, idsToIndexes_em, positions_em, sizes_em, texts,
                   i_em.nextId, i_em.nextIndex, NumberRects.size());
    for (int i = 0; i < texts.size(); i++)
    {
        auto id = texts[i];
        auto [x, y, w, h] = NumberRects[i];
        Position p{x, y};
        Size s{w, h};
        std::string content = std::to_string(i + 1);
        auto color = Config::TEXT_COLORS[i + 1];
        createText(i_em, id, content, color, 30, {w, h});
        textPositions.push_back(p);
        textSizes.push_back(s);
    }
    setPosition(positions_em, idsToIndexes_em, texts, textPositions);
    setSize(sizes_em, idsToIndexes_em, texts, textSizes);
    // Create images

    std::vector<Position> imagesPositions;
    std::vector<Size> imagesSizes;
    createEntities(entities_em, idsToIndexes_em, positions_em, sizes_em, images,
                   i_em.nextId, i_em.nextIndex, 2);
    auto flagId = images[0];
    createImage(i_em, flagId, Config::FLAG_IMAGE);
    auto bombId = images[1];
    createImage(i_em, bombId, Config::BOMB_PATH);
    {
        auto [x, y, w, h] = FlagRect;
        Position p{x, y};
        Size s{w, h};
        createImage(i_em, images[0], Config::FLAG_IMAGE);
        imagesPositions.push_back(p);
        imagesSizes.push_back(s);
    }
    {
        auto [x, y, w, h] = BombRect;
        Position p{x, y};
        Size s{w, h};
        createImage(i_em, images[1], Config::BOMB_PATH);
        imagesPositions.push_back(p);
        imagesSizes.push_back(s);
    }
    setPosition(positions_em, idsToIndexes_em, images, imagesPositions);
    setSize(sizes_em, idsToIndexes_em, images, imagesSizes);

    renderImages(i_em, p_renderer, images);
    renderTexts(i_em, p_renderer, texts);
    // SDL_RenderClear(p_renderer);
    SDL_SetRenderTarget(p_renderer, NULL);
}

}  // namespace TextureAtlas