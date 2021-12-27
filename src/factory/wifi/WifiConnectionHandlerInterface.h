#ifndef T_WIFI_CONNECTION_HANDLER_INTERFACE_H
#define T_WIFI_CONNECTION_HANDLER_INTERFACE_H

#include <Arduino.h>

class WifiConnectionHandlerInterface {

public:
    virtual void wifiConnected() = 0;
    virtual void wifiDisconnected() = 0;
};

#endif