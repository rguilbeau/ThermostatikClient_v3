#ifndef T_HEATING_HANDLER_H
#define T_HEATING_HANDLER_H

#include <Arduino.h>

#include "factory/programme/UntilDateHandlerInterface.h"
#include "factory/programme/OrderHandlerInterface.h"
#include "factory/dht/DhtFactory.h"
#include "factory/dht/DhtHandlerInterface.h"
#include "factory/relay/RelayFactory.h"
#include "factory/mqtt/MqttFactory.h"
#include "factory/mqtt/MqttMessageHandlerInterface.h"

#include "model/Programme.h"
#include "model/Device.h"
#include "model/Order.h"

#include "service/heating/Heating.h"
#include "service/MessageParserService.h"
#include "service/TopicService.h"

class HeatingHandler : 
    public UntilDateHandlerInterface, 
    public OrderHandlerInterface,
    public DhtHandlerInterface,
    public MqttMessageHandlerInterface
{

public:

    HeatingHandler(
        Programme *programme,
        Device *device,
        DhtFactory *dhtFactory,
        RelayFactory *relayFactory,
        MqttFactory *mqttFactory,
        MessageParserService *messageParserService,
        TopicService *topicService
    );

    void orderUpdated(Order *order) override;
    void untilDateHit() override;
    void temperatureChanged(float temperature) override;
    void temperatureIsNan() override; 
    void messageReceived(char *topic, char *message) override;

private:
    Programme *_programme;
    Device *_device;

    DhtFactory *_dhtFactory;
    RelayFactory *_relayFactory;
    MqttFactory *_mqttFactory;
    MessageParserService *_messageParserService;
    TopicService *_topicService;
};

#endif