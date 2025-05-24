cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 23)

set(PROJECT_NAME Sandbox)

project(${PROJECT_NAME} VERSION 1.0.0)

set(SDL2_DIR /opt/homebrew/opt/sdl2)
set(SDL2_IMAGE_DIR /opt/homebrew/opt/sdl2_image)
set(SDL2_TTF_DIR /opt/homebrew/opt/sdl2_ttf)




include_directories(
  ${PROJECT_NAME} PUBLIC
  ${SDL2_DIR}/include/SDL2
  ${SDL2_IMAGE_DIR}/include/SDL2
  ${SDL2_TTF_DIR}/include/SDL2
  ${CMAKE_SOURCE_DIR}
)

link_directories(
    ${SDL2_DIR}/lib
    ${SDL2_IMAGE_DIR}/lib
    ${SDL2_TTF_DIR}/lib
)



add_executable(${PROJECT_NAME}
              main.cpp
              "Globals.h"
              "Engine/Column.h"
              "Engine/Column.cpp"
              "Engine/Row.h"
              "Engine/Row.cpp"
              "Engine/Button.h"
              "Engine/Button.cpp"
              "Engine/Rectangle.h"
              "Engine/Rectangle.cpp"
              "Engine/Image.h"
              "Engine/Image.cpp"
              "Engine/Text.h"
              "Engine/Text.cpp"
              "Engine/Window.h"
              "Engine/Window.cpp"
              "Engine/Random.h"
              "Engine/UIElement.h"
              "Engine/UIElement.cpp"

              "Engine_DO/EntityID.h"
              "Engine_DO/Entity.h"
              "Engine_DO/Entity.cpp"
              "Engine_DO/Button.h"
              "Engine_DO/Button.cpp"
              "Engine_DO/EntityManager.h"
              "Engine_DO/EntityManager.cpp"
              "Engine_DO/World.h"
              "Engine_DO/World.cpp"
              "Engine_DO/WorldImpl.h"
              "Engine_DO/WorldImpl.cpp"
              "Engine_DO/Text.h"
              "Engine_DO/Text.cpp"
              "Engine_DO/Image.h"
              "Engine_DO/Image.cpp"
              "Engine_DO/TTFManager.h"
              "Engine_DO/TTFManager.cpp"

              "MS_DO/GameLoop.h"
              "MS_DO/GameLoop.cpp"
              
              "Minesweeper/Grid.h"
              "Minesweeper/Grid.cpp"
              "Minesweeper/Cell.h"
              "Minesweeper/Cell.cpp"
              "Minesweeper/NewGameButton.h"
              "Minesweeper/NewGameButton.cpp"
              "Minesweeper/UI.cpp"
              "Minesweeper/UI.h"
              "Minesweeper/GameSettings.cpp"
              "Minesweeper/FlagCounter.h"
              "Minesweeper/FlagCounter.cpp"
              "Minesweeper/DifficultyLabel.cpp"
              "Minesweeper/DifficultySwitch.cpp"
              "Minesweeper/MinesweeperAtlas.h"
              "Minesweeper/MinesweeperAtlas.cpp"
              )


target_link_libraries(${PROJECT_NAME}
  SDL2
  SDL2_image
  SDL2_ttf
  )

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets)