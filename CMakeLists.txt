cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 23)

project(Sandbox VERSION 1.0.0)

# Assets
set(ASSETS_SOURCES
    Image.cpp
    )

add_executable(Sandbox
              main.cpp
              ${ASSETS_SOURCES}
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