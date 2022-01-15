#include "TftFactory.h"

const String TftFactory::FONT_NOTO_15_PATH = "/font/NotoSansBold15.vlw";
const String TftFactory::FONT_NOTO_36_PATH = "/font/NotoSansBold36.vlw";

TftFactory::TftFactory(TFT_eSPI *driver, uint8_t pinBrightness)
{
    _driver = driver;
    _pinBrightness = pinBrightness;

    #ifdef DEBUG
        bool font_missing = false;
        if (!SPIFFS.exists(TftFactory::FONT_NOTO_15_PATH))
            font_missing = true;
        if (!SPIFFS.exists(TftFactory::FONT_NOTO_15_PATH))
            font_missing = true;

        if (font_missing) {
            Serial.println(F("ERROR : Font missing in SPIFFS, did you upload it?"));
        }
    #endif
}

void TftFactory::setBrightness(int percent) {
    percent = percent < 0 ? 0 : percent;
    percent = percent > 100 ? 100 : percent;

    int analogValue = (int) ((percent * 255) / 100);
    analogWrite(_pinBrightness, analogValue);
}

void TftFactory::print(int x, int y, TftText text)
{
    int height = getHeight(text.font);
    int color = getColor(text.color);
    int backgroundColor = getColor(text.background);

    loadFont(text.font);
    _driver->fillRect(
        x, y, text.width, 
        height, color
    );
    _driver->setCursor(x, y);
    _driver->setTextColor(color, backgroundColor);
    _driver->print(text.text);
}

void TftFactory::draw(int x, int y, TftImage image)
{
    switch(image) {
        case TftImage::IMAGE_THERMOMETER:
            drawFromSpiff(x, y, "/img/thermometer.bmp");
            break;
        case TftImage::IMAGE_THERMOMETER_FULL:
            drawFromSpiff(x, y, "/img/thermometer_full.bmp");
            break;
        case TftImage::IMAGE_THERMOMETER_THREE_QUARTER:
            drawFromSpiff(x, y, "/img/thermometer_three_quarter.bmp");
            break;
        case TftImage::IMAGE_THERMOMETER_HALF:
            drawFromSpiff(x, y, "/img/thermometer_half.bmp");
            break;
        case TftImage::IMAGE_THERMOMETER_QUARTER:
            drawFromSpiff(x, y, "/img/thermometer_quarter.bmp");
            break;
        case TftImage::IMAGE_THERMOMETER_EMPTY:
            drawFromSpiff(x, y, "/img/thermometer_empty.bmp");
            break;
        case TftImage::IMAGE_WIFI_OFF:
            drawFromSpiff(x, y, "/img/wifi_off.bmp");
            break;
        case TftImage::IMAGE_SERVER_OFF:
            drawFromSpiff(x, y, "/img/server_off.bmp");
            break;
        case TftImage::IMAGE_RECEIVER_OFF:
            drawFromSpiff(x, y, "/img/receiver_off.bmp");
            break;
        case TftImage::IMAGE_ORDER_PROGRAMME:
            drawFromSpiff(x, y, "/img/order_programme.bmp");
            break;
        case TftImage::IMAGE_ORDER_FORCED:
            drawFromSpiff(x, y, "/img/order_forced.bmp");
            break;
        case TftImage::IMAGE_ORDER_POWER_OFF:
            drawFromSpiff(x, y, "/img/order_power_off.bmp");
            break;
    }
}

int TftFactory::getColor(TftColor color)
{
    switch (color)
    {
    case TftColor::COLOR_GRAY :
        return 0;
    case TftColor::COLOR_WHITE :
        return 1;
    case TftColor::BG_DARK :
        return 2;    
    default:
        return 0;
    }
}

void TftFactory::loadFont(TftFont font)
{
    String fontStr = "NotoSansBold15";

    switch (font) {
        case TftFont::FONT_NOTO_15:
            _driver->loadFont("NotoSansBold15");
            break;
        case TftFont::FONT_NOTO_36:
            _driver->loadFont("NotoSansBold36");
            break;
        default:
            break;
    }
}

int TftFactory::getHeight(TftFont font)
{
    switch (font) {
        case TftFont::FONT_NOTO_15:
            return 18;
        case TftFont::FONT_NOTO_36:
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
            Serial.print("TFT image " + filename + " not found on SPIFFS");
        #endif
        return;
    }

    uint32_t seekOffset;
    uint16_t w, h, row;
    uint8_t r, g, b;

    uint32_t startTime = millis();

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

            #ifdef DEBUG
                Serial.print("BMP image " + filename + "loaded in ");
                Serial.print(millis() - startTime);
                Serial.println(" ms");
            #endif
        } else {
            #ifdef DEBUG
                Serial.println("BMP format not recognized for file : " + filename);
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