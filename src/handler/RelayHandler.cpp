#include "RelayHandler.h"

RelayHandler::RelayHandler(
    MqttFactory *mqttFactory,
    MessageParserService *messageParserService,
    TopicService *topicService
) {
    _mqttFactory = mqttFactory;
    _messageParserService = messageParserService;
    _topicService = topicService;
}

void RelayHandler::relayChanged(bool enable)
{
    String payload = _messageParserService->heatingToPayload(enable);
    _mqttFactory->publish(_topicService->getHeating(), payload.c_str());
}