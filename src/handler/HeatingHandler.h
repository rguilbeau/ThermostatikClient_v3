#ifndef T_HEATING_HANDLER_H
#define T_HEATING_HANDLER_H

#include <Arduino.h>

#include "factory/programme/UntilDateHandlerInterface.h"
#include "factory/programme/OrderHandlerInterface.h"
#include "factory/dht/DhtFactory.h"
#include "factory/dht/DhtHandlerInterface.h"
#include "factory/mqtt/MqttFactory.h"
#include "factory/mqtt/MqttMessageHandlerInterface.h"
#include "factory/receiver/ReceiverFactory.h"
#include "factory/programme/ModeHandlerInterface.h"

#include "model/Programme.h"
#include "model/Device.h"
#include "model/Order.h"

#include "service/heating/Heating.h"
#include "service/MessageParserService.h"
#include "service/TopicService.h"
#include "service/TftService.h"

class HeatingHandler : 
    public UntilDateHandlerInterface, 
    public OrderHandlerInterface,
    public DhtHandlerInterface,
    public MqttMessageHandlerInterface,
    public ModeHandlerInterface
{

public:

    HeatingHandler(
        Programme *programme,
        Device *device,
        DhtFactory *dhtFactory,
        MqttFactory *mqttFactory,
        ReceiverFactory *receiverFactory,
        MessageParserService *messageParserService,
        TopicService *topicService,
        TftService *tftService
    );

    void orderUpdated(Order *order) override;
    void orderAnticipating(Order *order) override;
    
    void untilDateHit() override;
    void temperatureChanged(float temperature) override;
    void temperatureIsNan() override; 
    void messageReceived(char *topic, char *message) override;
    void modeUpdated() override;

private:
    Programme *_programme;
    Device *_device;

    DhtFactory *_dhtFactory;
    MqttFactory *_mqttFactory;
    ReceiverFactory *_receiverFactory;

    MessageParserService *_messageParserService;
    TopicService *_topicService;
    TftService *_tftService;
};

#endif