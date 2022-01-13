#ifndef T_TFT_FACTORY_H
#define T_TFT_FACTORY_H

#include <Arduino.h>
#include "TFT_eSPI.h"

class TftFactory {

public:
    TftFactory(
        TFT_eSPI *driver,
        uint8_t pinBrightness
    );

private:
    TFT_eSPI *_driver;
    uint8_t _pinBrightness;
};

#endif