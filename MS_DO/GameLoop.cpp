#include "GameLoop.h"

#include "Engine_DO/EntityManager.h"
#include "Globals.h"
#include "Minesweeper/GameSettings.h"

namespace GameLoop
{
void init()
{
    auto em = Entity::createManager(14);
    auto& entities_em = em.entities;
    auto& children_em = em.children;
    auto& parents_em = em.parents;
    auto& sizes_em = em.sizes;
    auto& positions_em = em.positions;

    // UI init
    // Column
    Entity::EntityId layoutId = 0;
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

    Entity::EntityIdCollection res;
    Entity::EntityIdCollection toCreate{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

    Entity::createEntities(entities_em, em.ids, toCreate, em.nextId);

    // Sizes
    std::vector<Entity::Size> sizes;
    Entity::EntityIdCollection sizeIds;

    // Grid
    Entity::Size gridSize{(uint)GameSettings::GridWidth(),
                          (uint)GameSettings::GridHeight()};
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
    Entity::setSize(sizes_em, sizeIds, sizes);

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

    Entity::setType(entities_em, columns, column);
    Entity::setType(entities_em, rows, row);

    Entity::computeLayout(entities_em, children_em, sizes_em, positions_em, layoutId,
                          {Config::PADDING, Config::PADDING});
}
}  // namespace GameLoop