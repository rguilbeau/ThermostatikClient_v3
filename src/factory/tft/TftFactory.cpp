#include "TftFactory.h"

const String TftFactory::FONT_NOTO_15 = "NotoSansBold15";
const String TftFactory::FONT_NOTO_36 = "NotoSansBold36";

String TftFactory::formatTemperature(float temperature)
{
    char buff[6];
    dtostrf(temperature, 4, 1, buff);
    return (String(buff) + " 'C");
}

TftFactory::TftFactory(TFT_eSPI *driver, uint8_t pinBrightness)
{
    _driver = driver;
    _driver->init();

    _pinBrightness = pinBrightness;

    #ifdef DEBUG
        bool font_missing = false;
        if (!SPIFFS.exists("/" + TftFactory::FONT_NOTO_15 + ".vlw"))
            font_missing = true;
        if (!SPIFFS.exists("/" + TftFactory::FONT_NOTO_36 + ".vlw"))
            font_missing = true;

        if (font_missing) {
            Serial.println(F("ERROR : Font missing in SPIFFS, did you upload it?"));
        }
    #endif

    _fontLoaded = false;
    //pinMode(_pinBrightness, OUTPUT);
}

void TftFactory::setBrightness(int percent) {
    percent = percent < 0 ? 0 : percent;
    percent = percent > 100 ? 100 : percent;

    int analogValue = (int) ((percent * 255) / 100);
    analogWrite(_pinBrightness, analogValue);
}

void TftFactory::clear() {
    _driver->fillScreen(getColor(TftColor::BG_DARK));
    _driver->setRotation(3);
}

void TftFactory::print(int x, int y, TftText text)
{
    int height = getHeight(text.font);
    int color = getColor(text.color);
    uint32 backgroundColor = getColor(text.background);

    loadFont(text.font);
    _driver->fillRect(
        x, y, text.width, 
        height, backgroundColor
    );
    _driver->setCursor(x, y);
    _driver->setTextColor(color, backgroundColor);
    _driver->print(cleanString(text.text));
}

void TftFactory::fillRect(int x, int y, int width, int height, TftColor color)
{
    _driver->fillRect(x, y, width, height, getColor(color));
}

void TftFactory::draw(int x, int y, TftImage image)
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

uint32 TftFactory::getColor(TftColor color)
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
    /**
     * --- HACK ---
     * 
     * Le yield() doit être commenté dans la librairie TFT_eSPI
     * Dans la classe Smooth_font.cpp TFT_eSPI::loadMetrics(void)
     * 
     * Il est impossible de faire un yield() dans un callback asynchrone...
     * @todo Trouver une autre solution pour gérer le chargement des fonts dans un callback asynchrone
     * 
     */
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

int TftFactory::getHeight(TftFont font)
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

void TftFactory::drawFromSpiff(int x, int y, String filename)
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
    str.replace(F("Š"), F("S"));
    str.replace(F("š"), F("s"));
    str.replace(F("Ž"), F("Z"));
    str.replace(F("ž"), F("z"));
    str.replace(F("À"), F("A"));
    str.replace(F("Á"), F("A"));
    str.replace(F("Â"), F("A"));
    str.replace(F("Ã"), F("A"));
    str.replace(F("Ä"), F("A"));
    str.replace(F("Å"), F("A"));
    str.replace(F("Æ"), F("A"));
    str.replace(F("Ç"), F("C"));
    str.replace(F("È"), F("E"));
    str.replace(F("É"), F("E"));
    str.replace(F("Ê"), F("E"));
    str.replace(F("Ë"), F("E"));
    str.replace(F("Ì"), F("I"));
    str.replace(F("Í"), F("I"));
    str.replace(F("Î"), F("I"));
    str.replace(F("Ï"), F("I"));
    str.replace(F("Ñ"), F("N"));
    str.replace(F("Ò"), F("O"));
    str.replace(F("Ó"), F("O"));
    str.replace(F("Ô"), F("O"));
    str.replace(F("Õ"), F("O"));
    str.replace(F("Ö"), F("O"));
    str.replace(F("Ø"), F("O"));
    str.replace(F("Ù"), F("U"));
    str.replace(F("Ú"), F("U"));
    str.replace(F("Û"), F("U"));
    str.replace(F("Ü"), F("U"));
    str.replace(F("Ý"), F("Y"));
    str.replace(F("Þ"), F("B"));
    str.replace(F("ß"), F("Ss"));
    str.replace(F("à"), F("a"));
    str.replace(F("á"), F("a"));
    str.replace(F("â"), F("a"));
    str.replace(F("ã"), F("a"));
    str.replace(F("ä"), F("a"));
    str.replace(F("å"), F("a"));
    str.replace(F("æ"), F("a"));
    str.replace(F("ç"), F("c"));
    str.replace(F("è"), F("e"));
    str.replace(F("é"), F("e"));
    str.replace(F("ê"), F("e"));
    str.replace(F("ë"), F("e"));
    str.replace(F("ì"), F("i"));
    str.replace(F("í"), F("i"));
    str.replace(F("î"), F("i"));
    str.replace(F("ï"), F("i"));
    str.replace(F("ð"), F("o"));
    str.replace(F("ñ"), F("n"));
    str.replace(F("ò"), F("o"));
    str.replace(F("ó"), F("o"));
    str.replace(F("ô"), F("o"));
    str.replace(F("õ"), F("o"));
    str.replace(F("ö"), F("o"));
    str.replace(F("ø"), F("o"));
    str.replace(F("ù"), F("u"));
    str.replace(F("ú"), F("u"));
    str.replace(F("û"), F("u"));
    str.replace(F("ý"), F("y"));
    str.replace(F("þ"), F("b"));
    str.replace(F("ÿ"), F("y"));
    str.replace(F("œ"), F("oe"));
    str.replace(F("Œ"), F("OE"));
    return str;
}