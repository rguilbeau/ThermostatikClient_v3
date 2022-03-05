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
#include "factory/button/Button.h"
#include "factory/tft/TftFactory.h"
#include "factory/sleep/SleepFactory.h"

#include "handler/NetworkHandler.h"
#include "handler/TftAnimationHandler.h"
#include "handler/TftDateHandler.h"
#include "handler/HeatingHandler.h"
#include "handler/ReceiverStateHandler.h"
#include "handler/ButtonHandler.h"
#include "handler/OrderHandler.h"
#include "handler/SleepHandler.h"
#include "handler/DhtSmootherHandler.h"

#include "service/MessageParserService.h"
#include "service/TopicService.h"
#include "service/TftService.h"
#include "service/ProgrammeService.h"

#include "model/Device.h"
#include "model/Programme.h"

class Container {

public:

    static Container *get();

    ClockFactory *clockFactory();
    WifiFactory *wifiFactory();
    ReceiverFactory *receiverFactory();
    MqttFactory *mqttFactory();
    DhtFactory *dhtFactory();
    TftFactory *tftFactory();
    SleepFactory *sleepFactory();

    NetworkHandler *networkHandler();
    HeatingHandler *heatingHandler();
    ReceiverStateHandler *receiverStateHandler();
    ButtonHandler *buttonHandler();
    TftAnimationHandler *tftAnimationHandler();
    TftDateHandler *tftDateHandler();
    OrderHandler *orderHandler();
    SleepHandler *sleepHandler();
    DhtSmootherHandler *dhtSmootherHandler();

    Button *buttonMore();
    Button *buttonMinus();
    Button *buttonOk();

    Programme *programme();
    Device *device();

    TftService *tftService();

private:
    Container();

    static Container *instance;

    ClockFactory *_clockFactory;
    WifiFactory *_wifiFactory;
    ReceiverFactory *_receiverFactory;
    MqttFactory *_mqttFactory;
    DhtFactory *_dhtFactory;
    TftFactory *_tftFactory;
    SleepFactory *_sleepFactory;

    NetworkHandler *_networkHandler;
    HeatingHandler *_heatingHandler;
    ReceiverStateHandler *_receiverStateHandler;
    ButtonHandler *_buttonHandler;
    TftAnimationHandler *_tftAnimationHandler;
    TftDateHandler *_tftDateHandler;
    OrderHandler *_orderHandler;
    SleepHandler *_sleepHandler;
    DhtSmootherHandler *_dhtSmootherHandler;
    
    Button *_buttonMore;
    Button *_buttonMinus;
    Button *_buttonOk;

    ProgrammeService *_programmeService;
    MessageParserService *_messageParserService;
    TopicService *_topicService;
    TftService *_tftService;

    Programme *_programme;
    Device *_device;
};

#endif