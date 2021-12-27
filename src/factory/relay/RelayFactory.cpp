#include "RelayFactory.h"

RelayFactory::RelayFactory()
{
    _enable = false;
    _relayHandler = nullptr;
}

void RelayFactory::setHandler(RelayHandlerInterface *relayHandler)
{
    _relayHandler = relayHandler;
}

void RelayFactory::setStatus(bool status)
{
    if(status) {
        enable();
    } else {
        disable();
    }
}

void RelayFactory::enable()
{
    if(!_enable) {
        #ifdef DEBUG
            Serial.println("Relay : enable");
        #endif
        _enable = true;

        if(_relayHandler != nullptr) {
            _relayHandler->relayChanged(true);
        }
    } 
}

void RelayFactory::disable()
{
    if(_enable) {
        #ifdef DEBUG
            Serial.println("Relay : disable");
        #endif
        _enable = false;

        if(_relayHandler != nullptr) {
            _relayHandler->relayChanged(false);
        }
    }
}

bool RelayFactory::isEnable()
{
    return _enable;
}