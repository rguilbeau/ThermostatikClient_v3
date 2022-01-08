#include "HeatingHandler.h"

HeatingHandler::HeatingHandler(
    Programme *programme,
    Device *device,
    DhtFactory *dhtFactory,
    MqttFactory *mqttFactory,
    ReceiverFactory *receiverFactory,
    MessageParserService *messageParserService,
    TopicService *topicService
) {
    _programme = programme;
    _device = device;
    _dhtFactory = dhtFactory;
    _mqttFactory = mqttFactory;
    _messageParserService = messageParserService;
    _topicService = topicService;
    _receiverFactory = receiverFactory;
}

void HeatingHandler::orderUpdated(Order *order)
{
    #ifdef DEBUG
        Serial.print("Order updated, order:");
        Serial.println(order == nullptr ? "null" : order->getLabel());
    #endif

    _programme->setLastOrder(order);
    
    if(order != nullptr && _device->isForcedNextOrder()) {
        _device->setForced(false);

        String payload = _messageParserService->deviceToPayload(_device);
        _mqttFactory->publish(_topicService->getTemperatureControl(), payload.c_str());
    }

    Heating *heating = Heating::getMode(_device, _programme);
    bool regulationStatus = heating->regulationStatus(_dhtFactory->getTemperature());

    _receiverFactory->setState(regulationStatus);

    delete heating;
}

void HeatingHandler::untilDateHit()
{
    if(_device->isForcedUntilDate()) {
        #ifdef DEBUG
            Date now;
            Serial.print("Until date hint, date:");
            Serial.println(now.toShortFormat());
        #endif

        _device->setForced(false);

        String payload = _messageParserService->deviceToPayload(_device);
        _mqttFactory->publish(_topicService->getTemperatureControl(), payload.c_str());

        Heating *heating = Heating::getMode(_device, _programme);
        bool regulationStatus = heating->regulationStatus(_dhtFactory->getTemperature());

        _receiverFactory->setState(regulationStatus);

        delete heating;
    }
}

void HeatingHandler::temperatureChanged(float temperature)
{
    #ifdef DEBUG
        Serial.print("Temperature changed:");
        Serial.println(temperature);
    #endif

    String payload = _messageParserService->temperatureToPayload(temperature, false);
    _mqttFactory->publish(_topicService->getTemperatures(), payload.c_str());

    Heating *heating = Heating::getMode(_device, _programme);
    bool regulationStatus = heating->regulationStatus(temperature);
    _receiverFactory->setState(regulationStatus);
    delete heating;
}

void HeatingHandler::temperatureIsNan()
{
    #ifdef DEBUG
        Serial.println("Temperature is NaN");
    #endif

    String payload = _messageParserService->temperatureToPayload(0, true);
    _mqttFactory->publish(_topicService->getTemperatures(), payload.c_str());

    Heating *heating = Heating::getMode(_device, _programme);
    bool regulationStatus = heating->regulationStatus(99); //temperature NaN
    _receiverFactory->setState(regulationStatus);
    delete heating;
}

void HeatingHandler::messageReceived(char *topic, char *message)
{
    Date now;

    String topicStr = String(topic);

    #ifdef DEBUG
        Serial.print("Message received from:");
        Serial.print(topicStr);
        Serial.print(" payload:");
        Serial.println(message);
    #endif

    if(topicStr == String(_topicService->getDevice())) {
        _messageParserService->parseDevice(message, _device);
    } else if(topicStr == String(_topicService->getProgramme())) {
        _messageParserService->parseProgramme(message, _programme);        
        _programme->setLastOrder(_programme->findOrderAt(now));
    } else {
        #ifdef DEBUG
            Serial.println("Error : Unkonw topic");
        #endif
        return;
    }

    Heating *heating = Heating::getMode(_device, _programme);
    bool regulationStatus = heating->regulationStatus(_dhtFactory->getTemperature());
    _receiverFactory->setState(regulationStatus);
    delete heating;
}

void HeatingHandler::modeUpdated()
{
    String payload = _messageParserService->deviceToPayload(_device);
    _mqttFactory->publish(_topicService->getTemperatureControl(), payload.c_str());

    Heating *heating = Heating::getMode(_device, _programme);
    bool regulationStatus = heating->regulationStatus(_dhtFactory->getTemperature());
    _receiverFactory->setState(regulationStatus);
    delete heating;
}
