#ifndef T_MQTT_FACTORY_H
#define T_MQTT_FACTORY_H

#include <Arduino.h>
#include <AsyncMqttClient.h>

#include "Debug.h"

#include "MqttConnectionHandlerInterface.h"
#include "MqttMessageHandlerInterface.h"

class MqttFactory {

public:
    MqttFactory(
        AsyncMqttClient *client,
        const char *host, 
        uint16_t port, 
        const char *login, 
        const char *password
    );
    
    void setConnectionHandler(MqttConnectionHandlerInterface *connectionHandler);
    void setMessageHandler(MqttMessageHandlerInterface *messageHandler);

    void connect();
    bool isConnected();
    void subscribe(const char *topic);
    void publish(const char *topic, const char *payload);
    
private:
    AsyncMqttClient *_client;
    
    char *_messageBuff;
    const char *_host;
    uint16_t _port;
    const char *_login;

    MqttConnectionHandlerInterface *_connectionHandler;
    MqttMessageHandlerInterface *_messageHandler;

    void _clientConnected(bool sessionPresent);
    void _clientDisconnected(AsyncMqttClientDisconnectReason reason);
    void _clientMessageReceived(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total);
};

#endif