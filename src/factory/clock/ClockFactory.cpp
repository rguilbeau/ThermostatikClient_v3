#include "ClockFactory.h"
#include <iostream>

ClockFactory::ClockFactory()
{
    _ntpInitialized = false;
}

void ClockFactory::initNtp()
{
    #ifdef DEBUG
        Serial.println(F("NTP initialization"));
    #endif
    
    configTime(0, 0, "pool.ntp.org", "time.nist.gov"); // UTC
}

void ClockFactory::setNtpHandler(NtpHandlerInterface *ntpHandler)
{
    _ntpHandler = ntpHandler;
}

void ClockFactory::setHandlerSize(int size)
{
    _handlerSize = size;
    _handlers = new ClockHandlerInterface*[size];
    _handlersDelays = new int[size]; 
    _lastCheck = new unsigned long[size];
}

void ClockFactory::setHandler(int index, int delay, ClockHandlerInterface *handler)
{
    if(index < _handlerSize) {
        _handlers[index] = handler;
        _handlersDelays[index] = delay;
        _lastCheck[index] = 0;
    }
}

void ClockFactory::loop()
{

    if(!_ntpInitialized) {
        time_t now = time(nullptr);
        if(now >= 8 * 3600 * 2) {
            struct tm timeinfo;
            gmtime_r(&now, &timeinfo);
            _ntpInitialized = true;
        }

        if(_ntpInitialized && _ntpHandler != nullptr) {
            _ntpHandler->ntpInitialized();
        }
    }

    unsigned long currentMillis = millis();
    for(int i = 0; i < _handlerSize; i++) {
        if(_lastCheck[i] + _handlersDelays[i] < currentMillis) {
            _lastCheck[i] = currentMillis;
            _handlers[i]->clockHandle();
        }
    }

}