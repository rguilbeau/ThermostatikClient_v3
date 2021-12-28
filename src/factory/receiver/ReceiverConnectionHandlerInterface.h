#ifndef T_RECEIVER_CONNECTION_HANDLER_INTERFACE_H
#define T_RECEIVER_CONNECTION_HANDLER_INTERFACE_H

class ReceiverConnectionHandlerInterface {

public:
    virtual void receiverConnected() = 0;

    virtual void receiverDisconnected() = 0;
};

#endif