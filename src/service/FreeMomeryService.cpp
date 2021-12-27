#include "FreeMemoryService.h"


FreeMemoryService::FreeMemoryService(unsigned short delay)
{
    _delay = delay;
    _lastCheck = 0;
    _lastFreeMemory = 0;
}

void FreeMemoryService::loop()
{
    if(_lastCheck + _delay < millis()) {
        _lastCheck = millis();

        uint16_t freeMemory = ESP.getFreeHeap();
        if(_lastFreeMemory != freeMemory) {
            _lastFreeMemory = freeMemory;

            #ifdef DISPLAY_FREE_MEMORY
                Serial.print(F("* Free memory : "));
                Serial.print(_lastFreeMemory);
                Serial.println(F(" *"));
            #endif
        }
    }
}