#ifndef T_THERMOMETER_RENDER_H
#define T_THERMOMETER_RENDER_H

#include <Arduino.h>
#include "factory/tft/type/TftImage.h"

struct ThermometerRender {
    TftImage image = TftImage::IMAGE_THERMOMETER;
};


#endif