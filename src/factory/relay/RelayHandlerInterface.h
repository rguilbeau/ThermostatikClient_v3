#ifndef T_RELAY_HANDLER_INTERFACE_H
#define T_RELAY_HANDLER_INTERFACE_H

class RelayHandlerInterface {

public:

    virtual void relayChanged(bool enable) = 0;

};

#endif