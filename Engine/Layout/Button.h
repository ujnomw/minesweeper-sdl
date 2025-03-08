#pragma once

#include "Globals.h"
#include "RectangleUnit.h"

namespace Layout
{
class Button : public RectangleUnit
{
   public:
    Button(int x, int y, int w, int h)
    {
        RectangleUnit::SetBox(Box({x, y, w, h}));
        RectangleUnit::SetColor(Config::BUTTON_COLOR);
    };
};
};  // namespace Layout