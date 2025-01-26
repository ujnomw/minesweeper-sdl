cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 23)

project(Sandbox VERSION 1.0.0)


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

              # Files that will be added later:
              # "Minesweeper/Grid.h"
              # "Minesweeper/UI.h"
              # "Minesweeper/Cell.h"
              # "Minesweeper/Cell.cpp"
              # "Minesweeper/NewGameButton.h"
              )

# Variables storing SDL framework locations
set(SDL2
  /Library/Frameworks/SDL2.framework)
set(SDL2_image
  /Library/Frameworks/SDL2_image.framework)
set(SDL2_ttf
  /Library/Frameworks/SDL2_ttf.framework)

target_link_libraries(
  Sandbox PRIVATE
  -framework ${SDL2}/Versions/A/SDL2
  -framework ${SDL2_image}/Versions/A/SDL2_image
  -framework ${SDL2_ttf}/Versions/A/SDL2_ttf
)

target_include_directories(
  Sandbox PRIVATE
  ${SDL2}/Versions/A/Headers
  ${SDL2_image}/Versions/A/Headers
  ${SDL2_ttf}/Versions/A/Headers
)

# Add the frameworks to the search path
target_link_options(Sandbox PRIVATE "-F/Library/Frameworks")