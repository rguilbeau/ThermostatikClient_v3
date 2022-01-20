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
#include "factory/receiver/ReceiverFactory.h"
#include "factory/mqtt/MqttConnectionHandlerInterface.h"
#include "factory/wifi/WifiConnectionHandlerInterface.h"
#include "factory/receiver/ReceiverConnectionHandlerInterface.h"

#include "factory/dht/DhtFactory.h"

#include "service/MessageParserService.h"
#include "service/TopicService.h"
#include "service/TftService.h"

class NetworkHandler : 
    public MqttConnectionHandlerInterface, 
    public WifiConnectionHandlerInterface, 
    public NtpHandlerInterface,
    public ReceiverConnectionHandlerInterface
{
public:

    NetworkHandler(
        ClockFactory *clockFactory,
        WifiFactory *wifiFactory,
        ReceiverFactory *receiverFactory,
        MqttFactory *mqttFactory, 
        DhtFactory *dhtFactory,
        TopicService *topicService,
        MessageParserService *messageParserService,
        TftService *tftService
    );

    void ntpInitialized() override;

    void mqttConnected() override;
    void mqttDisconnected() override;

    void wifiConnected() override;
    void wifiDisconnected() override;

    void receiverConnected() override;
    void receiverDisconnected() override;

private:
    ClockFactory *_clockFactory;
    WifiFactory *_wifiFactory;
    ReceiverFactory *_receiverFactory;
    DhtFactory *_dhtFactory;
    MqttFactory *_mqttFactory;
    
    TopicService *_topicService;
    MessageParserService *_messageParserService;
    TftService *_tftService;

    Ticker _mqttReconnectTimer;
    Ticker _wifiReconnectTimer;
};

#endif