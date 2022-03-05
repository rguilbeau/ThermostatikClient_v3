#include "ReceiverStateHandler.h"

ReceiverStateHandler::ReceiverStateHandler(
    MqttFactory *mqttFactory,
    MessageParserService *messageParserService,
    TopicService *topicService,
    TftService *tftService,
    TftAnimationHandler *tftAnimationHandler
) {
    _mqttFactory = mqttFactory;
    _messageParserService = messageParserService;
    _topicService = topicService;
    _tftService = tftService;
    _tftAnimationHandler = tftAnimationHandler;
}

void ReceiverStateHandler::receiverStateChanged(bool state)
{
    #ifdef DEBUG
        Serial.print(F("Receiver state changed, state:"));
        Serial.println(state);
    #endif

    TemperatureLabelRender temperatureLabelRender;
    temperatureLabelRender.text = state ? F("En chauffe...") : F("Consigne atteinte");
    _tftService->setTemperatureLabelRender(temperatureLabelRender);

    ThermometerRender thermometerRender;
    thermometerRender.image = state ? TftImage::IMAGE_THERMOMETER_EMPTY : TftImage::IMAGE_THERMOMETER;
    _tftService->setThermometerRender(thermometerRender);
    _tftAnimationHandler->animateThermometer(state);
    
    String payload = _messageParserService->heatingToPayload(state);
    _mqttFactory->publish(_topicService->getHeating(), payload.c_str());
}