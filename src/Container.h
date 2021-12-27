#ifndef T_CONTAINER_H
#define T_CONTAINER_H

#include <Arduino.h>

#include <AsyncMqttClient.h>

#include "Secret.h"

#include "factory/wifi/WifiFactory.h"
#include "factory/mqtt/MqttFactory.h"
#include "factory/dht/DhtFactory.h"
#include "factory/relay/RelayFactory.h"
#include "factory/clock/ClockFactory.h"
#include "factory/programme/ProgrammeFactory.h"

#include "handler/NetworkHandler.h"
#include "handler/RelayHandler.h"
#include "handler/ThermometerAnimationHandler.h"
#include "handler/HeatingHandler.h"

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
    MqttFactory *mqttFactory();
    DhtFactory *dhtFactory();
    RelayFactory *relayFactory();

    NetworkHandler *networkHandler();
    RelayHandler *relayHandler();
    ThermometerAnimationHandler *thermometerAnimationHandler();
    HeatingHandler *heatingHandler();

    Programme *programme();
    Device *device();

private:
    Container();

    static Container *instance;

    ProgrammeFactory *_programmeFactory;
    ClockFactory *_clockFactory;
    WifiFactory *_wifiFactory;
    MqttFactory *_mqttFactory;
    DhtFactory *_dhtFactory;
    RelayFactory *_relayFactory;

    NetworkHandler *_networkHandler;
    RelayHandler *_relayHandler;
    ThermometerAnimationHandler *_thermometerAnimationHandler;
    HeatingHandler *_heatingHandler;

    MessageParserService *_messageParserService;
    TopicService *_topicService;

    Programme *_programme;
    Device *_device;
};

#endif