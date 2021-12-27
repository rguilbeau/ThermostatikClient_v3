#ifndef T_MQTT_CONNECTION_HANDLER_INTERFACE_H
#define T_MQTT_CONNECTION_HANDLER_INTERFACE_H

#include <Arduino.h>

class MqttConnectionHandlerInterface {

public:
    virtual void mqttConnected() = 0;
    virtual void mqttDisconnected() = 0;

};

#endif