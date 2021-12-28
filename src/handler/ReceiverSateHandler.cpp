#include "ReceiverStateHandler.h"

ReceiverStateHandler::ReceiverStateHandler(
    MqttFactory *mqttFactory,
    MessageParserService *messageParserService,
    TopicService *topicService
) {
    _mqttFactory = mqttFactory;
    _messageParserService = messageParserService;
    _topicService = topicService;
}

void ReceiverStateHandler::receiverStateChanged(bool state)
{
    #ifdef DEBUG
        Serial.print("Receiver state changed, state:");
        Serial.println(state);
    #endif

    String payload = _messageParserService->heatingToPayload(state);
    _mqttFactory->publish(_topicService->getHeating(), payload.c_str());
}