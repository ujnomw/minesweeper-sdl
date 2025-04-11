cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 23)

project(Sandbox VERSION 1.0.0)

set(SDL2_DIR /opt/homebrew/opt/sdl2)
set(SDL2_IMAGE_DIR /opt/homebrew/opt/sdl2_image)
set(SDL2_TTF_DIR /opt/homebrew/opt/sdl2_ttf)

include_directories(
  Sandbox PRIVATE
  ${CMAKE_SOURCE_DIR}
  ${SDL2_DIR}/include/SDL2
  ${SDL2_IMAGE_DIR}/include/SDL2
  ${SDL2_TTF_DIR}/include/SDL2
)

link_directories(
    ${SDL2_DIR}/lib
    ${SDL2_IMAGE_DIR}/lib
    ${SDL2_TTF_DIR}/lib
)

add_executable(Sandbox
              main.cpp
              Globals.h
              "Engine/Button.h"
              "Engine/Rectangle.h"
              "Engine/Image.h"
              "Engine/Text.h"
              "Engine/Window.h"
              "Engine/Random.h"
              
              "Minesweeper/UI.h"
              "Minesweeper/Grid.h"
              "Minesweeper/UI.h"
              "Minesweeper/Cell.h"
              "Minesweeper/Cell.cpp"
              "Minesweeper/NewGameButton.h"
              )


target_link_libraries(Sandbox
  SDL2
  SDL2_image
  SDL2_ttf
  )