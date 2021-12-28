#ifndef T_CONTAINER_H
#define T_CONTAINER_H

#include <Arduino.h>

#include <AsyncMqttClient.h>

#include "Secret.h"

#include "factory/wifi/WifiFactory.h"
#include "factory/receiver/ReceiverFactory.h"
#include "factory/mqtt/MqttFactory.h"
#include "factory/dht/DhtFactory.h"
#include "factory/clock/ClockFactory.h"
#include "factory/programme/ProgrammeFactory.h"

#include "handler/NetworkHandler.h"
#include "handler/ThermometerAnimationHandler.h"
#include "handler/HeatingHandler.h"
#include "handler/ReceiverStateHandler.h"

#include "service/MessageParserService.h"
#include "service/TopicService.h"

#include "model/Device.h"
#include "model/Programme.h"

class Container {

public:

    static Container *get();

    ProgrammeFactory *programmeFactory();
    ClockFactory *clockFactory();
    WifiFactory *wifiFactory();
    ReceiverFactory *receiverFactory();
    MqttFactory *mqttFactory();
    DhtFactory *dhtFactory();

    NetworkHandler *networkHandler();
    ThermometerAnimationHandler *thermometerAnimationHandler();
    HeatingHandler *heatingHandler();
    ReceiverStateHandler *receiverStateHandler();

    Programme *programme();
    Device *device();

private:
    Container();

    static Container *instance;

    ProgrammeFactory *_programmeFactory;
    ClockFactory *_clockFactory;
    WifiFactory *_wifiFactory;
    ReceiverFactory *_receiverFactory;
    MqttFactory *_mqttFactory;
    DhtFactory *_dhtFactory;

    NetworkHandler *_networkHandler;
    ThermometerAnimationHandler *_thermometerAnimationHandler;
    HeatingHandler *_heatingHandler;
    ReceiverStateHandler *_receiverStateHandler;

    MessageParserService *_messageParserService;
    TopicService *_topicService;

    Programme *_programme;
    Device *_device;
};

#endif