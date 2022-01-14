#ifndef T_TFT_FACTORY_H
#define T_TFT_FACTORY_H

#include <Arduino.h>
#include "TFT_eSPI.h"
#include "type/TftFont.h"
#include "type/TftText.h"
#include "type/TftImage.h"

class TftFactory {

public:
    TftFactory(
        TFT_eSPI *driver,
        uint8_t pinBrightness
    );

    void setBrightness(int percent);
    void print(TftText text);
    void draw(TftImage image);
    void loop();

private:
    TFT_eSPI *_driver;
    uint8_t _pinBrightness;

    void loadFont(TftFont font);
    void drawFromSpiff(int x, int y, String image);
    int getColor(TftColor color);
    int getHeight(TftFont font);
    uint16_t read16(fs::File &f);
    uint32_t read32(fs::File &f);
};

#endif