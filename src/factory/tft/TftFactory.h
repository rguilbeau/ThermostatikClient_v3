#ifndef T_TFT_FACTORY_H
#define T_TFT_FACTORY_H

#include <Arduino.h>
#include "FS.h"

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
    void print(int x, int y, TftText text);
    void draw(int x, int y, TftImage image);
    void loop();

private:
    static const String FONT_NOTO_15_PATH;
    static const String FONT_NOTO_36_PATH;
    
    TFT_eSPI *_driver;
    uint8_t _pinBrightness;

    void loadFont(TftFont font);
    void drawFromSpiff(int x, int y, String image);
    int getColor(TftColor color);
    int getHeight(TftFont font);
    uint16_t read16(File &f);
    uint32_t read32(File &f);
};

#endif