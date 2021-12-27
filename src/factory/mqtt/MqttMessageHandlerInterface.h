#ifndef T_MQTT_MESSAGE_HANDLER_INTERFACE_H
#define T_MQTT_MESSAGE_HANDLER_INTERFACE_H

#include <Arduino.h>

class MqttMessageHandlerInterface {

public:

    virtual void messageReceived(char *topic, char *message) = 0;

};

#endif