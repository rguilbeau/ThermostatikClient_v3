#include "NetworkHandler.h"

NetworkHandler::NetworkHandler(
    ClockFactory *clockFactory,
    WifiFactory *wifiFactory, 
    MqttFactory *mqttFactory, 
    DhtFactory *dhtFactory,
    RelayFactory *relayFactory,
    TopicService *topicService,
    MessageParserService *messageParserService
) {
    _wifiFactory = wifiFactory; 
    _mqttFactory = mqttFactory;
    _dhtFactory = dhtFactory;
    _relayFactory = relayFactory;
    _topicService = topicService;
    _messageParserService = messageParserService;
}

void NetworkHandler::ntpInitialized()
{
    Date::timeInitialized = true;
}

void NetworkHandler::mqttConnected()
{
    // subscribe to channels
    _mqttFactory->subscribe(_topicService->getProgramme());
    _mqttFactory->subscribe(_topicService->getDevice());

    // send current temperature
    String payloadTemperature = _messageParserService->temperatureToPayload(
        _dhtFactory->getTemperature(),
        _dhtFactory->isNan()
    );
    _mqttFactory->publish(_topicService->getTemperatures(), payloadTemperature.c_str());

    // send relay status
    String payloadHeating = _messageParserService->heatingToPayload(
        _relayFactory->isEnable()
    );
    _mqttFactory->publish(_topicService->getHeating(), payloadHeating.c_str());

    // ask to refresh programme
    _mqttFactory->publish(_topicService->getAsker(), "update requested");
}

void NetworkHandler::mqttDisconnected()
{
    if(_wifiFactory->isConnected()) {
        _mqttReconnectTimer.once(2, std::bind(&MqttFactory::connect, _mqttFactory));
    } else {
        #ifdef DEBUG
            Serial.println("Network factory can't connect to MQTT : wifi is disconnected");
        #endif
    }
}

void NetworkHandler::wifiConnected()
{
    _clockFactory->initNtp();
    _mqttReconnectTimer.once(1, std::bind(&MqttFactory::connect, _mqttFactory));
}

void NetworkHandler::wifiDisconnected()
{
    _mqttReconnectTimer.detach();
    _wifiReconnectTimer.once(2, std::bind(&WifiFactory::connect, _wifiFactory));
}
