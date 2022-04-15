#ifndef T_HEATING_HANDLER_H
#define T_HEATING_HANDLER_H

#include <Arduino.h>

#include <Ticker.h>

#include "handler/interface/UntilDateHandlerInterface.h"
#include "handler/interface/OrderUpdatedHandlerInterface.h"
#include "factory/temperature_sensor/TemperatureSensorFactory.h"
#include "factory/temperature_sensor/TemperatureSensorHandlerInterface.h"
#include "factory/mqtt/MqttFactory.h"
#include "factory/mqtt/MqttMessageHandlerInterface.h"
#include "factory/receiver/ReceiverFactory.h"
#include "factory/sleep/SleepFactory.h"
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
    public TemperatureSensorHandlerInterface,
    public MqttMessageHandlerInterface,
    public ModeHandlerInterface
{

public:

    HeatingHandler(
        Programme *programme,
        Device *device,
        TemperatureSensorFactory *temperatureSensorFactory,
        MqttFactory *mqttFactory,
        ReceiverFactory *receiverFactory,
        SleepFactory *sleepFactory,
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
    void modeUpdated(bool isQuickRender) override;

private:
    Programme *_programme;
    Device *_device;

    TemperatureSensorFactory *_temperatureSensorFactory;
    MqttFactory *_mqttFactory;
    ReceiverFactory *_receiverFactory;
    SleepFactory *_sleepFactory;

    MessageParserService *_messageParserService;
    ProgrammeService *_programmeService;
    TopicService *_topicService;
    TftService *_tftService;

    Ticker differedModeUpdatedTicker;
    void differedModeUpdated();
};

#endif