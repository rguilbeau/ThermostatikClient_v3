#ifndef T_RELAY_HANDLER_H
#define T_RELAY_HANDLER_H

#include <Arduino.h>

#include "Debug.h"

#include "factory/relay/RelayHandlerInterface.h"
#include "factory/mqtt/MqttFactory.h"
#include "factory/dht/DhtFactory.h"

#include "service/MessageParserService.h"
#include "service/TopicService.h"


class RelayHandler : public RelayHandlerInterface {

public:

    RelayHandler(
        MqttFactory *mqttFactory,
        MessageParserService *messageParserService,
        TopicService *topicService
    );

    void relayChanged(bool enable) override;

private:
    MqttFactory *_mqttFactory;
    MessageParserService *_messageParserService;
    TopicService *_topicService;
};

#endif