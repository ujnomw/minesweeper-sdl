#include "GameLoop.h"

#include "Engine_DO/EntityManager.h"
#include "Engine_DO/Image.h"
#include "Engine_DO/Text.h"
#include "Globals.h"
#include "Minesweeper/GameSettings.h"

namespace GameLoop
{
// Column
Entity::EntityId layoutId;
// Grid
Entity::EntityId gridId = 1;
// Lower Two Rows Container
// Could be row or col depending on the layout
Entity::EntityId lowerRowsContainerId = 2;
// NewGame + Flag Row
Entity::EntityId newGameRowId = 3;
// Diff Level Row
Entity::EntityId difficultyRowId = 4;
// Flag Counter Row
Entity::EntityId flagCounterId = 5;

// New Game Button
Entity::EntityId newGameButtonId = 6;
// // New Game Text
// Entity::EntityId newGameTextId = 7;

// // Flag Counter Image
// Entity::EntityId flagCounterImageId = 8;
// // Flag Counter Text
// Entity::EntityId flagCounterTextId = 9;

// Diff Label Rect
Entity::EntityId difficultyLabelId = 10;
// // Diff Label Text
// Entity::EntityId difficultyTextId = 11;

// Switch Button
Entity::EntityId switchButtonId = 12;
// // Switch Image
// Entity::EntityId switchImageId = 13;

// I N D E X E S after creation

// Column
const Entity::EntityId layoutIndex = 0;
// Grid
const Entity::EntityId gridIndex = 1;
// Lower Two Rows Container
// Could be row or col depending on the layout
const Entity::EntityId lowerRowsContainerIndex = 2;
// NewGame + Flag Row
const Entity::EntityId newGameRowIndex = 3;
// Diff Level Row
Entity::EntityId difficultyRowIndex = 4;
// Flag Counter Row
const Entity::EntityId flagCounterIndex = 5;

// New Game Button
const Entity::EntityId newGameButtonIndex = 6;
// // New Game Text
// Entity::EntityId newGameTextId = 7;

// // Flag Counter Image
// Entity::EntityId flagCounterImageId = 8;
// // Flag Counter Text
// Entity::EntityId flagCounterTextId = 9;

// Diff Label Rect
const Entity::EntityId difficultyLabelIndex = 10;
// // Diff Label Text
// Entity::EntityId difficultyTextId = 11;

// Switch Button
const Entity::EntityId switchButtonIndex = 12;
// // Switch Image
// Entity::EntityId switchImageId = 13;

bool init(Entity::EntityManager* em)
{
    auto& entities_em = em->entities;
    auto& children_em = em->children;
    auto& parents_em = em->parents;
    auto& sizes_em = em->sizes;
    auto& positions_em = em->positions;
    auto& idsToIndexes_em = em->idsToIndexes;

    // UI init

    Entity::EntityIdCollection res;
    Entity::EntityIdCollection toCreate{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

    Entity::createEntities(entities_em, idsToIndexes_em, positions_em, sizes_em, res,
                           em->nextId, em->nextIndex, 14);

    layoutId = res[layoutIndex];
    gridId = res[gridIndex];
    lowerRowsContainerId = res[lowerRowsContainerIndex];
    newGameRowId = res[newGameRowIndex];
    difficultyRowId = res[difficultyRowIndex];
    flagCounterId = res[flagCounterIndex];
    newGameButtonId = res[newGameButtonIndex];
    difficultyLabelId = res[difficultyLabelIndex];
    switchButtonId = res[switchButtonIndex];
    // Layout heirarchy
    Entity::EntityIdCollection layoutChildren = {gridId, lowerRowsContainerId};
    Entity::setParent(parents_em, children_em, layoutChildren, layoutId);
    // Lower control rows heirarchy
    Entity::EntityIdCollection lowerRowsContainerChildren = {newGameRowId,
                                                             difficultyRowId};
    Entity::setParent(parents_em, children_em, lowerRowsContainerChildren,
                      lowerRowsContainerId);
    // New Game + Flag counter heirarchy
    Entity::EntityIdCollection newGameRowChildren = {newGameButtonId, flagCounterId};
    Entity::setParent(parents_em, children_em, newGameRowChildren, newGameRowId);
    // Diff row heirarchy
    Entity::EntityIdCollection difficultyRowChildren = {difficultyLabelId,
                                                        switchButtonId};
    Entity::setParent(parents_em, children_em, difficultyRowChildren, difficultyRowId);
    // // Flag counter heirarchy
    // Entity::EntityIdCollection flagCounterChildren = {flagCounterImageId,
    //                                                   flagCounterTextId};
    // Entity::setParent(parents_em, children_em, flagCounterChildren, flagCounterId);

    // Sizes
    std::vector<Entity::Size> sizes;
    Entity::EntityIdCollection sizeIds;

    // Grid
    Entity::Size gridSize{GameSettings::GridWidth(), GameSettings::GridHeight()};
    sizes.push_back(gridSize);
    sizeIds.push_back(gridId);
    // New Game Button
    Entity::Size newGameButtonSize{Config::NEW_GAME_BUTTON_WIDTH,
                                   Config::FOOTER_HEIGHT - Config::PADDING};
    sizes.push_back(newGameButtonSize);
    sizeIds.push_back(newGameButtonId);
    // Flag Counter
    Entity::Size flagCounterSize{Config::FLAG_COUNTER_WIDTH,
                                 Config::FOOTER_HEIGHT - Config::PADDING};
    sizes.push_back(flagCounterSize);
    sizeIds.push_back(flagCounterId);
    // Diff label
    Entity::Size difficultyLabelSize{Config::DIFFICULTY_LABEL_WIDTH,
                                     Config::FOOTER_HEIGHT - Config::PADDING};
    sizes.push_back(difficultyLabelSize);
    sizeIds.push_back(difficultyLabelId);
    // Switch
    Entity::Size switchButtonSize{Config::FLAG_COUNTER_WIDTH,
                                  Config::FOOTER_HEIGHT - Config::PADDING};
    sizes.push_back(switchButtonSize);
    sizeIds.push_back(switchButtonId);

    // Set sizes for leave* elements
    Entity::setSize(sizes_em, idsToIndexes_em, sizeIds, sizes);

    // Set element types
    std::string newGameWording = "NEW GAME";
    Entity::createText(*em, newGameButtonId, newGameWording, {0, 0, 0, 255}, 20,
                       sizes_em[newGameButtonId]);
    std::string levelWording = "LEVEL: " + GameSettings::GetNextMode();
    Entity::createText(*em, difficultyLabelId, levelWording, {0, 0, 0, 255}, 20,
                       sizes_em[difficultyLabelId]);
    Entity::createImage(*em, switchButtonId, Config::REFRESH_IMAGE);

    // Setting types for layout
    Entity::EntityIdCollection columns = {layoutId};
    Entity::EntityIdCollection rows = {difficultyRowId, newGameRowId};
    if (GameSettings::GetMode() == Hard)
    {
        rows.push_back(lowerRowsContainerId);
    }
    else
    {
        columns.push_back(lowerRowsContainerId);
    }

    Entity::EntityType column = "column";
    Entity::EntityType row = "row";

    Entity::setType(entities_em, idsToIndexes_em, columns, column);
    Entity::setType(entities_em, idsToIndexes_em, rows, row);

    Entity::computeLayout(entities_em, idsToIndexes_em, children_em, sizes_em,
                          positions_em, layoutId, {Config::PADDING, Config::PADDING});
    return true;
}

void render(Entity::EntityManager& em, SDL_Renderer* i_renderer)
{
    auto& entities_em = em.entities;
    auto& children_em = em.children;
    auto& parents_em = em.parents;
    auto& sizes_em = em.sizes;
    auto& positions_em = em.positions;

    for (int id = 0; id < entities_em.size(); id++)
    {
        auto& e = entities_em[id];
        auto [w, h] = sizes_em[id];
        if (w < 1 || h < 1) continue;
        auto [r, g, b, a] = e.d_backgroundColor;
        auto [x, y] = positions_em[id];

        SDL_Rect rect{(int)x, (int)y, (int)w, (int)h};
        SDL_SetRenderDrawColor(i_renderer, r, g, b, a);
        SDL_RenderDrawRect(i_renderer, &rect);
    }
    Entity::EntityIdCollection textIds = {newGameButtonId, difficultyLabelId};
    Entity::renderTexts(em, i_renderer, textIds);
    Entity::EntityIdCollection imageIds = {switchButtonId};
    Entity::renderImages(em, i_renderer, imageIds);
    SDL_RenderPresent(i_renderer);
}
}  // namespace GameLoop