#ifndef T_RECEIVER_STATE_HANDLER_H
#define T_RECEIVER_STATE_HANDLER_H

#include <Arduino.h>

#include "factory/receiver/ReceiverStateHandlerInterface.h"
#include "factory/mqtt/MqttFactory.h"

#include "service/MessageParserService.h"
#include "service/TopicService.h"

class ReceiverStateHandler : public ReceiverStateHandlerInterface {

public:
    ReceiverStateHandler(
        MqttFactory *mqttFactory,
        MessageParserService *messageParserService,
        TopicService *topicService
    );
    
    void receiverStateChanged(bool state) override;

private:
    MqttFactory *_mqttFactory;
    MessageParserService *_messageParserService;
    TopicService *_topicService;
};

#endif