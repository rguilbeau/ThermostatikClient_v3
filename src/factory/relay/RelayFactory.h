#ifndef T_RELAY_FACTORY_H
#define T_RELAY_FACTORY_H

#include <Arduino.h>
#include "Debug.h"

#include "RelayHandlerInterface.h"

class RelayFactory {

public:
    RelayFactory();

    void setHandler(RelayHandlerInterface *relayHandler);
    void setStatus(bool status);
    void enable();
    void disable();
    bool isEnable();

private:
    bool _enable;
    RelayHandlerInterface *_relayHandler;
};


#endif