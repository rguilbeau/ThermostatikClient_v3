#ifndef T_RECEIVER_HANDLER_INTERFACE_H
#define T_RECEIVER_HANDLER_INTERFACE_H

#include <Arduino.h>

class ReceiverStateHandlerInterface {
    
public:

    virtual void receiverStateChanged(bool state) = 0;

};

#endif