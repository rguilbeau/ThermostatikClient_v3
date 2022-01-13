#include "TftFactory.h"

TftFactory::TftFactory(TFT_eSPI *driver, uint8_t pinBrightness)
{
    _driver = driver;
    _pinBrightness = pinBrightness;
}

void TftFactory::setBrightness(int percent) {
    percent = percent < 0 ? 0 : percent;
    percent = percent > 100 ? 100 : percent;

    int analogValue = (int) ((percent * 255) / 100);
    analogWrite(_pinBrightness, analogValue);
}