#ifndef T_FREE_MEMORY_SERVICE_H
#define T_FREE_MEMORY_SERVICE_H

#include <Arduino.h>

class FreeMemoryService {

public:

    FreeMemoryService(unsigned short delay);

    void loop();

private:
    unsigned short _delay;
    unsigned long _lastCheck;
    uint16_t _lastFreeMemory;
};

#endif