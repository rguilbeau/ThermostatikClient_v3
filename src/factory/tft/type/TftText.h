#ifndef T_TFT_TEXT_H
#define T_TFT_TEXT_H

#include <Arduino.h>
#include "TftFont.h"
#include "TftColor.h"

struct TftText
{
    unsigned short width = 0;
    TftColor color = TftColor::COLOR_WHITE;
    TftColor background = TftColor::BG_DARK;
    TftFont font = TftFont::SMALL;
    String text = "";
};


#endif