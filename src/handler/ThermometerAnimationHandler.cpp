#include "ThermometerAnimationHandler.h"

ThermometerAnimationHandler::ThermometerAnimationHandler()
{
    _lastTimeMin = 0;
}

void ThermometerAnimationHandler::clockHandle()
{
    if(Date::timeInitialized) {
        Date now;
        if(now.getTimeMin() != _lastTimeMin) {
            _lastTimeMin = now.getTimeMin();
            Serial.println(now.toLongFormat());
        }
    } else {
        Serial.println("Initialisation de la date...");
    }
}