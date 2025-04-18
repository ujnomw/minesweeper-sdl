cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 23)

project(Sandbox VERSION 1.0.0)

set(SDL2_DIR /opt/homebrew/opt/sdl2)
set(SDL2_IMAGE_DIR /opt/homebrew/opt/sdl2_image)
set(SDL2_TTF_DIR /opt/homebrew/opt/sdl2_ttf)

include_directories(
  Sandbox PUBLIC
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

add_executable(Sandbox
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


target_link_libraries(Sandbox
  SDL2
  SDL2_image
  SDL2_ttf
  )