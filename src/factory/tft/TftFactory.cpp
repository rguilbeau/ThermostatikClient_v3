#include "TftFactory.h"


const String TftFactory::FONT_NOTO_15 = "NotoSansBold15";
const String TftFactory::FONT_NOTO_36 = "NotoSansBold36";

String TftFactory::formatTemperature(float temperature)
{
    char buff[6];
    dtostrf(temperature, 4, 1, buff);
    return (String(buff) + F(" 'C"));
}

TftFactory::TftFactory(TFT_eSPI *driver, uint8_t pinBrightness)
{
    _driver = driver;
    _driver->init();

    _pinBrightness = pinBrightness;

    #ifdef DEBUG
        bool font_missing = false;
        if (!SPIFFS.exists(F("/") + TftFactory::FONT_NOTO_15 + F(".vlw")))
            font_missing = true;
        if (!SPIFFS.exists(F("/") + TftFactory::FONT_NOTO_36 + F(".vlw")))
            font_missing = true;

        if (font_missing) {
            Serial.println(F("ERROR : Font missing in SPIFFS, did you upload it?"));
        }
    #endif

    _fontLoaded = false;

    #ifdef ESP8266
        //pinMode(_pinBrightness, OUTPUT);
    #else 
        ledcSetup(0, 5000, 8);
        ledcAttachPin(_pinBrightness, 0);
    #endif
}

void TftFactory::setBrightness(unsigned short percent) {
    percent = percent < 0 ? 0 : percent;
    percent = percent > 100 ? 100 : percent;

    unsigned short analogValue = (int) ((percent * 255) / 100);

    #ifdef ESP8266
        analogWrite(_pinBrightness, analogValue);
    #else
        ledcWrite(0, analogValue);
    #endif
}

void TftFactory::clear() {
    _driver->fillScreen(getColor(TftColor::BG_DARK));
    _driver->setRotation(3);
}

void TftFactory::print(unsigned short x, unsigned short y, TftText text)
{
    unsigned short height = getHeight(text.font);
    unsigned short color = getColor(text.color);
    uint32_t backgroundColor = getColor(text.background);

    loadFont(text.font);
    _driver->fillRect(
        x, y, text.width, 
        height, backgroundColor
    );
    _driver->setCursor(x, y);
    _driver->setTextColor(color, backgroundColor);
    _driver->print(cleanString(text.text));
}

void TftFactory::fillRect(unsigned short x, unsigned short y, unsigned short width, unsigned short height, TftColor color)
{
    _driver->fillRect(x, y, width, height, getColor(color));
}

void TftFactory::draw(unsigned short x, unsigned short y, TftImage image)
{
    switch(image) {
        case TftImage::IMAGE_THERMOMETER:
            drawFromSpiff(x, y, F("/th.bmp"));
            break;
        case TftImage::IMAGE_THERMOMETER_FULL:
            drawFromSpiff(x, y, F("/th4.bmp"));
            break;
        case TftImage::IMAGE_THERMOMETER_THREE_QUARTER:
            drawFromSpiff(x, y, F("/th3.bmp"));
            break;
        case TftImage::IMAGE_THERMOMETER_HALF:
            drawFromSpiff(x, y, F("/th2.bmp"));
            break;
        case TftImage::IMAGE_THERMOMETER_QUARTER:
            drawFromSpiff(x, y, F("/th1.bmp"));
            break;
        case TftImage::IMAGE_THERMOMETER_EMPTY:
            drawFromSpiff(x, y, F("/th0.bmp"));
            break;
        case TftImage::IMAGE_WIFI_OFF:
            drawFromSpiff(x, y, F("/wifi.bmp"));
            break;
        case TftImage::IMAGE_SERVER_OFF:
            drawFromSpiff(x, y, F("/server.bmp"));
            break;
        case TftImage::IMAGE_RECEIVER_OFF:
            drawFromSpiff(x, y, F("/tower.bmp"));
            break;
        case TftImage::IMAGE_ORDER_PROGRAMME:
            drawFromSpiff(x, y, F("/arrow.bmp"));
            break;
        case TftImage::IMAGE_ORDER_FORCED:
            drawFromSpiff(x, y, F("/hand.bmp"));
            break;
        case TftImage::IMAGE_ORDER_POWER_OFF:
            drawFromSpiff(x, y, F("/off.bmp"));
            break;
        case TftImage::IMAGE_ORDER_ANTICIPATING:
            drawFromSpiff(x, y, F("/clock.bmp"));
    }
}

uint32_t TftFactory::getColor(TftColor color)
{
    switch (color)
    {
    case TftColor::COLOR_GRAY :
        return TFT_DARKGREY;
    case TftColor::COLOR_WHITE :
        return TFT_WHITE;
    case TftColor::BG_DARK :
        return TFT_BLACK;    
    default:
        return 0;
    }
}

void TftFactory::loadFont(TftFont font)
{
    if(!_fontLoaded || _tftFontLoaded != font) {
        switch (font) {
            case TftFont::SMALL:
                _driver->loadFont(TftFactory::FONT_NOTO_15, false);
                _tftFontLoaded = TftFont::SMALL;
                break;
            case TftFont::LARGE:
                _driver->loadFont(TftFactory::FONT_NOTO_36, false);
                _tftFontLoaded = TftFont::LARGE;
                break;
            default:
                break;
        }
        _fontLoaded = true;
    }
}

unsigned short TftFactory::getHeight(TftFont font)
{
    switch (font) {
        case TftFont::SMALL:
            return 18;
        case TftFont::LARGE:
            return 31;
        default:
            return 0;
    }
}

void TftFactory::drawFromSpiff(unsigned short x, unsigned short y, String filename)
{
    // @see https://github.com/Bodmer/TFT_eSPI/tree/master/examples/Generic/TFT_SPIFFS_BMP
    if ((x >= _driver -> width()) || (y >= _driver -> height())) return;

    fs::File bmpFS;

    // Open requested file
    bmpFS = SPIFFS.open(filename, "r");

    if (!bmpFS) {
        #ifdef DEBUG
            Serial.print(F("TFT immage "));
            Serial.print(filename);
            Serial.println(F(" not found on SPIFFS"));
        #endif
        return;
    }

    uint32_t seekOffset;
    uint16_t w, h, row;
    uint8_t r, g, b;

    if (read16(bmpFS) == 0x4D42) {
        read32(bmpFS);
        read32(bmpFS);
        seekOffset = read32(bmpFS);
        read32(bmpFS);
        w = read32(bmpFS);
        h = read32(bmpFS);

        if ((read16(bmpFS) == 1) && (read16(bmpFS) == 24) && (read32(bmpFS) == 0)) {
            y += h - 1;

            bool oldSwapBytes = _driver -> getSwapBytes();
            _driver -> setSwapBytes(true);
            bmpFS.seek(seekOffset);

            uint16_t padding = (4 - ((w * 3) & 3)) & 3;
            uint8_t lineBuffer[w * 3 + padding];

            for (row = 0; row < h; row++) {

                bmpFS.read(lineBuffer, sizeof(lineBuffer));
                uint8_t * bptr = lineBuffer;
                uint16_t * tptr = (uint16_t * ) lineBuffer;
                // Convert 24 to 16 bit colours
                for (uint16_t col = 0; col < w; col++) {
                    b = * bptr++;
                    g = * bptr++;
                    r = * bptr++;
                    * tptr++ = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
                }

                // Push the pixel row to screen, pushImage will crop the line if needed
                // y is decremented as the BMP image is drawn bottom up
                _driver -> pushImage(x, y--, w, 1, (uint16_t * ) lineBuffer);
            }

            _driver->setSwapBytes(oldSwapBytes);
        } else {
            #ifdef DEBUG
                Serial.print(F("BMP format not recognized for file : "));
                Serial.println(filename);
            #endif
        }
    }
    bmpFS.close();
}

uint16_t TftFactory::read16(File &f) {
    uint16_t result;
    ((uint8_t *)&result)[0] = f.read(); // LSB
    ((uint8_t *)&result)[1] = f.read(); // MSB
    return result;
}

uint32_t TftFactory::read32(File &f) {
    uint32_t result;
    ((uint8_t *)&result)[0] = f.read(); // LSB
    ((uint8_t *)&result)[1] = f.read();
    ((uint8_t *)&result)[2] = f.read();
    ((uint8_t *)&result)[3] = f.read(); // MSB
    return result;
}

String TftFactory::cleanString(String str) {
    str.replace(F("??"), F("S"));
    str.replace(F("??"), F("s"));
    str.replace(F("??"), F("Z"));
    str.replace(F("??"), F("z"));
    str.replace(F("??"), F("A"));
    str.replace(F("??"), F("A"));
    str.replace(F("??"), F("A"));
    str.replace(F("??"), F("A"));
    str.replace(F("??"), F("A"));
    str.replace(F("??"), F("A"));
    str.replace(F("??"), F("A"));
    str.replace(F("??"), F("C"));
    str.replace(F("??"), F("E"));
    str.replace(F("??"), F("E"));
    str.replace(F("??"), F("E"));
    str.replace(F("??"), F("E"));
    str.replace(F("??"), F("I"));
    str.replace(F("??"), F("I"));
    str.replace(F("??"), F("I"));
    str.replace(F("??"), F("I"));
    str.replace(F("??"), F("N"));
    str.replace(F("??"), F("O"));
    str.replace(F("??"), F("O"));
    str.replace(F("??"), F("O"));
    str.replace(F("??"), F("O"));
    str.replace(F("??"), F("O"));
    str.replace(F("??"), F("O"));
    str.replace(F("??"), F("U"));
    str.replace(F("??"), F("U"));
    str.replace(F("??"), F("U"));
    str.replace(F("??"), F("U"));
    str.replace(F("??"), F("Y"));
    str.replace(F("??"), F("B"));
    str.replace(F("??"), F("Ss"));
    str.replace(F("??"), F("a"));
    str.replace(F("??"), F("a"));
    str.replace(F("??"), F("a"));
    str.replace(F("??"), F("a"));
    str.replace(F("??"), F("a"));
    str.replace(F("??"), F("a"));
    str.replace(F("??"), F("a"));
    str.replace(F("??"), F("c"));
    str.replace(F("??"), F("e"));
    str.replace(F("??"), F("e"));
    str.replace(F("??"), F("e"));
    str.replace(F("??"), F("e"));
    str.replace(F("??"), F("i"));
    str.replace(F("??"), F("i"));
    str.replace(F("??"), F("i"));
    str.replace(F("??"), F("i"));
    str.replace(F("??"), F("o"));
    str.replace(F("??"), F("n"));
    str.replace(F("??"), F("o"));
    str.replace(F("??"), F("o"));
    str.replace(F("??"), F("o"));
    str.replace(F("??"), F("o"));
    str.replace(F("??"), F("o"));
    str.replace(F("??"), F("o"));
    str.replace(F("??"), F("u"));
    str.replace(F("??"), F("u"));
    str.replace(F("??"), F("u"));
    str.replace(F("??"), F("y"));
    str.replace(F("??"), F("b"));
    str.replace(F("??"), F("y"));
    str.replace(F("??"), F("oe"));
    str.replace(F("??"), F("OE"));
    return str;
}