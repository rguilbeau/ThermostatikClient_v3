#ifndef T_RECEIVER_STATE_HANDLER_H
#define T_RECEIVER_STATE_HANDLER_H

#include <Arduino.h>

#include "factory/receiver/ReceiverStateHandlerInterface.h"
#include "factory/mqtt/MqttFactory.h"

#include "handler/TftAnimationHandler.h"

#include "service/MessageParserService.h"
#include "service/TopicService.h"
#include "service/TftService.h"

class ReceiverStateHandler : public ReceiverStateHandlerInterface {

public:
    ReceiverStateHandler(
        MqttFactory *mqttFactory,
        MessageParserService *messageParserService,
        TopicService *topicService,
        TftService *tftService,
        TftAnimationHandler *tftAnimationHandler
    );
    
    void receiverStateChanged(bool state) override;

private:
    Device *_device;
    MqttFactory *_mqttFactory;
    MessageParserService *_messageParserService;
    TopicService *_topicService;
    TftService *_tftService;
    TftAnimationHandler *_tftAnimationHandler;
};

#endif