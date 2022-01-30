#ifndef T_HEATING_HANDLER_H
#define T_HEATING_HANDLER_H

#include <Arduino.h>

#include "handler/interface/UntilDateHandlerInterface.h"
#include "handler/interface/OrderUpdatedHandlerInterface.h"
#include "factory/dht/DhtFactory.h"
#include "factory/dht/DhtHandlerInterface.h"
#include "factory/mqtt/MqttFactory.h"
#include "factory/mqtt/MqttMessageHandlerInterface.h"
#include "factory/receiver/ReceiverFactory.h"
#include "handler/interface/ModeHandlerInterface.h"

#include "model/Programme.h"
#include "model/Device.h"
#include "model/Order.h"

#include "service/heating/Heating.h"
#include "service/MessageParserService.h"
#include "service/TopicService.h"
#include "service/TftService.h"
#include "service/ProgrammeService.h"

class HeatingHandler : 
    public UntilDateHandlerInterface, 
    public OrderUpdatedHandlerInterface,
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
        ProgrammeService *programmeService,
        TopicService *topicService,
        TftService *tftService
    );

    void orderUpdated() override;
    void orderAnticipating() override;
    
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
    ProgrammeService *_programmeService;
    TopicService *_topicService;
    TftService *_tftService;
};

#endif