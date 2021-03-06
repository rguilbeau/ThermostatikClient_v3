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

    void setBrightness(unsigned short percent);
    void clear();
    void print(unsigned short x, unsigned short y, TftText text);
    void draw(unsigned short x, unsigned short y, TftImage image);
    void fillRect(unsigned short x, unsigned short y, unsigned short width, unsigned short height, TftColor color);
    void loop();

    static String formatTemperature(float temperature);

private:
    static const String FONT_NOTO_15;
    static const String FONT_NOTO_36;
    
    TFT_eSPI *_driver;
    uint8_t _pinBrightness;

    TftFont _tftFontLoaded = TftFont::SMALL;
    bool _fontLoaded;
    
    void loadFont(TftFont font);
    void drawFromSpiff(unsigned short x, unsigned short y, String image);
    uint32_t getColor(TftColor color);
    unsigned short getHeight(TftFont font);
    uint16_t read16(File &f);
    uint32_t read32(File &f);

    String cleanString(String str);
};

#endif