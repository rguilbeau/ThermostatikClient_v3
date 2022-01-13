#include "TftFactory.h"

TftFactory::TftFactory(TFT_eSPI *driver, uint8_t pinBrightness)
{
    _driver = driver;
    _pinBrightness = pinBrightness;
}