#ifndef T_TFT_TEXT_H
#define T_TFT_TEXT_H

#include <Arduino.h>
#include "TftFont.h"
#include "TftColor.h"

struct TftText
{
    int x = 0;
    int y = 0;
    int width = 0;
    TftColor color = TftColor::COLOR_WHITE;
    TftColor background = TftColor::BG_DARK;
    TftFont font = TftFont::FONT_NOTO_15;
    String text = "";
};


#endif