#include "MqttFactory.h"


MqttFactory::MqttFactory(
    AsyncMqttClient *client,
    const char *host, 
    uint16_t port, 
    const char *login, 
    const char *password
) {
    _messageBuff = new char[2048]; //1034
    _connectionHandler = nullptr;
    _messageHandler = nullptr;

    _host = host;
    _port = port;
    _login = login;

    _client = client;
    _client->setCredentials(_login, password);
    _client->setServer(_host, _port);
    _client->setClientId(_login);

    _client->onConnect(std::bind(&MqttFactory::_clientConnected, this, std::placeholders::_1));
    _client->onDisconnect(std::bind(&MqttFactory::_clientDisconnected, this, std::placeholders::_1));
    _client->onMessage(std::bind(&MqttFactory::_clientMessageReceived, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6));
}

void MqttFactory::setConnectionHandler(MqttConnectionHandlerInterface *connectionHandler)
{
    _connectionHandler = connectionHandler;
}

void MqttFactory::setMessageHandler(MqttMessageHandlerInterface *messageHandler)
{
    _messageHandler = messageHandler;
}

void MqttFactory::connect()
{
    #ifdef DEBUG
        Serial.print(F("Connect to MQTT : "));
        Serial.print(_host);
        Serial.print(":");
        Serial.print(String(_port));
        Serial.print(" / login : ");
        Serial.println(_login);
    #endif
    _client->connect();
}

bool MqttFactory::isConnected()
{
    return _client->connected();
}

void MqttFactory::subscribe(const char *topic)
{
    if(_client->connected()) {
        #ifdef DEBUG
            Serial.print(F("MQTT Subscribe to "));
            Serial.println(String(topic));
        #endif

        _client->subscribe(topic, 2);
    }

}

void MqttFactory::publish(const char *topic,  const char *payload)
{
    if(_client->connected()) {
        #ifdef DEBUG
            Serial.print(F("MQTT Publish to "));
            Serial.print(String(topic));
            Serial.print(F(" | payload : "));
            Serial.println(String(payload));
        #endif

        _client->publish(topic, 0, true, payload);
    }
}

void MqttFactory::_clientConnected(bool sessionPresent)
{
    #ifdef DEBUG
        Serial.println(F("MQTT connected"));
    #endif

    if(_connectionHandler != nullptr) {
        _connectionHandler->mqttConnected();
    }
}

void MqttFactory::_clientDisconnected(AsyncMqttClientDisconnectReason reason)
{
    #ifdef DEBUG
        Serial.print(F("MQTT disconnected : "));
        switch(reason){
            case AsyncMqttClientDisconnectReason::TCP_DISCONNECTED:
                Serial.println(F("TCP_DISCONNECTED"));
                break;
            case AsyncMqttClientDisconnectReason::MQTT_UNACCEPTABLE_PROTOCOL_VERSION:
                Serial.println(F("MQTT_UNACCEPTABLE_PROTOCOL_VERSION"));
                break;
            case AsyncMqttClientDisconnectReason::MQTT_IDENTIFIER_REJECTED:
                Serial.println(F("MQTT_IDENTIFIER_REJECTED"));
                break;
            case AsyncMqttClientDisconnectReason::MQTT_SERVER_UNAVAILABLE:
                Serial.println(F("MQTT_SERVER_UNAVAILABLE"));
                break;
            case AsyncMqttClientDisconnectReason::MQTT_MALFORMED_CREDENTIALS:
                Serial.println(F("MQTT_MALFORMED_CREDENTIALS"));
                break;
            case AsyncMqttClientDisconnectReason::MQTT_NOT_AUTHORIZED:
                Serial.println(F("MQTT_NOT_AUTHORIZED"));
                break;
            case AsyncMqttClientDisconnectReason::ESP8266_NOT_ENOUGH_SPACE:
                Serial.println(F("ESP8266_NOT_ENOUGH_SPACE"));
                break;
            case AsyncMqttClientDisconnectReason::TLS_BAD_FINGERPRINT:
                Serial.println(F("TLS_BAD_FINGERPRIN"));
                break;
            default:
                Serial.println(F("UNKNOWN REASON"));
                break;
        }
    #endif

    if(_connectionHandler != nullptr) {
         _connectionHandler->mqttDisconnected();
    }
}

void MqttFactory::_clientMessageReceived(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total)
{

    #ifdef DEBUG
        if(len != total) {
            Serial.print("MQTT partial message (index:");
            Serial.print(index);
            Serial.print(", length:");
            Serial.print(len);
            Serial.print(", total:");
            Serial.print(total);
            Serial.println(")");
        }
    #endif

    for(size_t i = 0; i < len; i++) {
        _messageBuff[i + index] = payload[i];
    }
    
    if (index + len == total) { // at end
        if(_messageHandler != nullptr) {
            _messageHandler->messageReceived(topic, _messageBuff);
        }
        memset(_messageBuff, 0, 2048);
    }
}