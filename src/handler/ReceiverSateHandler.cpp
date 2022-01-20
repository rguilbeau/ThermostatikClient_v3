#include "ReceiverStateHandler.h"

ReceiverStateHandler::ReceiverStateHandler(
    MqttFactory *mqttFactory,
    MessageParserService *messageParserService,
    TopicService *topicService,
    TftService *tftService
) {
    _mqttFactory = mqttFactory;
    _messageParserService = messageParserService;
    _topicService = topicService;
    _tftService = tftService;
}

void ReceiverStateHandler::receiverStateChanged(bool state)
{
    #ifdef DEBUG
        Serial.print("Receiver state changed, state:");
        Serial.println(state);
    #endif

    TemperatureLabelRender temperatureLabelRender;
    temperatureLabelRender.text = state ? "En chauffe..." : "Consigne atteinte";
    _tftService->setTemperatureLabelRender(temperatureLabelRender);

    ThermometerRender thermometerRender;
    thermometerRender.image = state ? TftImage::IMAGE_THERMOMETER_EMPTY : TftImage::IMAGE_THERMOMETER;
    _tftService->setThermometerRender(thermometerRender);

    String payload = _messageParserService->heatingToPayload(state);
    _mqttFactory->publish(_topicService->getHeating(), payload.c_str());
}