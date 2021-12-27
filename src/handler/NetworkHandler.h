#ifndef T_NETWORK_HANDLER_H
#define T_NETWORK_HANDLER_H

#include <Arduino.h>
#include <Ticker.h>
#include "Debug.h"

#include "utils/Date.h"

#include "factory/clock/NtpHandlerInterface.h"
#include "factory/clock/ClockFactory.h"
#include "factory/mqtt/MqttFactory.h"
#include "factory/wifi/WifiFactory.h"
#include "factory/mqtt/MqttConnectionHandlerInterface.h"
#include "factory/wifi/WifiConnectionHandlerInterface.h"
#include "factory/relay/RelayFactory.h"
#include "factory/dht/DhtFactory.h"

#include "service/MessageParserService.h"
#include "service/TopicService.h"

class NetworkHandler : public MqttConnectionHandlerInterface, public WifiConnectionHandlerInterface, public NtpHandlerInterface {

public:

    NetworkHandler(
        ClockFactory *clockFactory,
        WifiFactory *wifiFactory, 
        MqttFactory *mqttFactory, 
        DhtFactory *dhtFactory,
        RelayFactory *relayFactory,
        TopicService *topicService,
        MessageParserService *messageParserService
    );

    void ntpInitialized() override;

    void mqttConnected() override;
    void mqttDisconnected() override;

    void wifiConnected() override;
    void wifiDisconnected() override;

private:
    ClockFactory *_clockFactory;
    WifiFactory *_wifiFactory; 
    DhtFactory *_dhtFactory;
    MqttFactory *_mqttFactory;
    RelayFactory *_relayFactory;
    
    TopicService *_topicService;
    MessageParserService *_messageParserService;

    Ticker _mqttReconnectTimer;
    Ticker _wifiReconnectTimer;
};

#endif