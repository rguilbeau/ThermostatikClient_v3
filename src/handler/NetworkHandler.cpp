#include "NetworkHandler.h"

NetworkHandler::NetworkHandler(
    ClockFactory *clockFactory,
    WifiFactory *wifiFactory,
    ReceiverFactory *receiverFactory,
    MqttFactory *mqttFactory, 
    DhtFactory *dhtFactory,
    TopicService *topicService,
    MessageParserService *messageParserService,
    TftService *tftService
) {
    _wifiFactory = wifiFactory; 
    _mqttFactory = mqttFactory;
    _dhtFactory = dhtFactory;
    _topicService = topicService;
    _messageParserService = messageParserService;
    _receiverFactory = receiverFactory;
    _tftService = tftService;
}

void NetworkHandler::ntpInitialized()
{
    Date::timeInitialized = true;
}

void NetworkHandler::mqttConnected()
{
    ServerStateRender render;
    render.connected = true;
    _tftService->setServerStateRender(render);

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
        _receiverFactory->getReceiverState()
    );
    _mqttFactory->publish(_topicService->getHeating(), payloadHeating.c_str());

    // ask to refresh programme
    _mqttFactory->publish(_topicService->getAsker(), "update requested");
}

void NetworkHandler::mqttDisconnected()
{
    ServerStateRender render;
    render.connected = false;
    _tftService->setServerStateRender(render);

    if(_wifiFactory->isConnected()) {

        #ifdef ESP8266
        _mqttReconnectTimer.once(2, std::bind(&MqttFactory::connect, _mqttFactory));
        #else
         _mqttReconnectTimer.once(2, +[](MqttFactory *mqttFactory){
             mqttFactory->connect();
         }, _mqttFactory);
        #endif

    } else {
        #ifdef DEBUG
            Serial.println(F("Network factory can't connect to MQTT : wifi is disconnected"));
        #endif
    }
}

void NetworkHandler::wifiConnected()
{
    WifiStateRender render;
    render.connected = true;
    _tftService->setWifiStateRender(render);

    _clockFactory->initNtp();

    #ifdef ESP8266
        _mqttReconnectTimer.once(1, std::bind(&MqttFactory::connect, _mqttFactory));
    #else
        _mqttReconnectTimer.once(1, +[](MqttFactory *mqttFactory) {
            mqttFactory->connect();
        }, _mqttFactory);
    #endif
    
}

void NetworkHandler::wifiDisconnected()
{
    WifiStateRender render;
    render.connected = false;
    _tftService->setWifiStateRender(render);

    _mqttReconnectTimer.detach();

    #ifdef ESP8266
        _wifiReconnectTimer.once(2, std::bind(&WifiFactory::connect, _wifiFactory));
    #else
        _wifiReconnectTimer.once(2, +[](WifiFactory *wifiFactory) {
            wifiFactory->connect();
        }, _wifiFactory);
    #endif

}


void NetworkHandler::receiverConnected()
{
    #ifdef DEBUG
        Serial.println(F("Receiver connected"));
    #endif

    ReceiverStateRender render;
    render.connected = true;
    _tftService->setReceiverStateRender(render);
}

void NetworkHandler::receiverDisconnected()
{
    #ifdef DEBUG
        Serial.println(F("Receiver disconnected"));
    #endif

    ReceiverStateRender render;
    render.connected = false;
    _tftService->setReceiverStateRender(render);
}
