#include "SleepHandler.h"

SleepHandler::SleepHandler(Device *device, TftFactory *tftFactory)
{
    _device = device;
    _tftFactory = tftFactory;
}

void SleepHandler::goSleep()
{
    #ifdef DEBUG
        Serial.print(F("Go to sleep. Set brightness:"));
        Serial.print(_device->getBrightnessMin());
        Serial.println(F("%"));
    #endif
    
    _tftFactory->setBrightness(_device->getBrightnessMin());
}

void SleepHandler::wakeUp() 
{
    #ifdef DEBUG
        Serial.print(F("Wake up. Set brightness:"));
        Serial.print(_device->getBrightnessMax());
        Serial.println(F("%"));
    #endif

    _tftFactory->setBrightness(_device->getBrightnessMax());
}