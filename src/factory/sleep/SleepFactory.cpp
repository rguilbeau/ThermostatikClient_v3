#include "SleepFactory.h"

SleepFactory::SleepFactory(int delay)
{
    _delay = delay;
    _lastWakeUp = 0;
    _sleeping = false;
}

void SleepFactory::setHandler(SleepHandlerInterface *handler)
{
    _handler = handler;
}

void SleepFactory::invokeHandler()
{
    if(_handler != nullptr) {
        if(_sleeping) {
            _handler->goSleep();
        } else {
            _handler->wakeUp();
        }
    }
}

bool SleepFactory::isWakeUp()
{
    return !_sleeping;
}

void SleepFactory::wakeUp()
{
    _lastWakeUp = millis();
    if(_handler != nullptr && _sleeping) {
        _handler->wakeUp();
        _sleeping = false;
    }
}

void SleepFactory::loop()
{
    if(_handler != nullptr && !_sleeping) {
        if(_lastWakeUp + _delay < millis()) {
            _handler->goSleep();
            _sleeping = true;
        }
    }
}