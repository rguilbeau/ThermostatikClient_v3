#ifndef T_ORDER_RENDER_H
#define T_ORDER_RENDER_H

#include <Arduino.h>
#include "factory/tft/type/TftImage.h"

struct OrderRender {
    TftImage icon = TftImage::IMAGE_ORDER_POWER_OFF;
    String temperature = "Eteint";
    String label = "Aucune chauffe";
    String info = "";
};

#endif