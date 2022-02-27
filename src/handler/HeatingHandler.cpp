#include "HeatingHandler.h"

HeatingHandler::HeatingHandler(
    Programme *programme,
    Device *device,
    DhtFactory *dhtFactory,
    MqttFactory *mqttFactory,
    ReceiverFactory *receiverFactory,
    MessageParserService *messageParserService,
    ProgrammeService *programmeService,
    TopicService *topicService,
    TftService *tftService
) {
    _programme = programme;
    _device = device;
    _dhtFactory = dhtFactory;
    _mqttFactory = mqttFactory;
    _messageParserService = messageParserService;
    _programmeService = programmeService;
    _topicService = topicService;
    _receiverFactory = receiverFactory;
    _tftService = tftService;
}

void HeatingHandler::orderUpdated()
{
    Order *order = _programme->getLastOrder();

    #ifdef DEBUG
        Serial.print("Order updated, order:");
        Serial.println(order == nullptr ? "null" : order->getLabel());
    #endif

    String payload = _messageParserService->anticipatingToPayload(nullptr);
    _mqttFactory->publish(_topicService->getAnticipating(), payload.c_str());

    if(order != nullptr && _device->isForcedNextOrder()) {
        _device->setForced(false);

        String payload = _messageParserService->deviceToPayload(_device);
        _mqttFactory->publish(_topicService->getTemperatureControl(), payload.c_str());
    }

    if(_device->isProgrammeMode()) {
        Heating *heating = Heating::getMode(_device, _programme);
        bool regulationStatus = heating->regulationStatus(_dhtFactory->getTemperature());

        _receiverFactory->setState(regulationStatus);
        _tftService->setOrderRender(heating->getRender());

        delete heating;
    }
}

void HeatingHandler::orderAnticipating()
{
    Order *order = _programme->getAnticipatingOrder();

    #ifdef DEBUG
        Serial.print("Order anticipating, order:");
        Serial.println(order == nullptr ? "null" : order->getLabel());
    #endif

    if(_device->isProgrammeMode()) {
        String payload = _messageParserService->anticipatingToPayload(order);
        _mqttFactory->publish(_topicService->getAnticipating(), payload.c_str());
        
        Heating *heating = Heating::getMode(_device, _programme);
        bool regulationStatus = heating->regulationStatus(_dhtFactory->getTemperature());

        _receiverFactory->setState(regulationStatus);
        _tftService->setOrderRender(heating->getRender());

        delete heating;
    }
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

        Order *publishAnticipatingOrder = nullptr;
        if(_device->isProgrammeMode()) {
            publishAnticipatingOrder = _programme->getAnticipatingOrder();
        }

        payload = _messageParserService->anticipatingToPayload(publishAnticipatingOrder);
        _mqttFactory->publish(_topicService->getAnticipating(), payload.c_str());

        Heating *heating = Heating::getMode(_device, _programme);
        bool regulationStatus = heating->regulationStatus(_dhtFactory->getTemperature());

        _receiverFactory->setState(regulationStatus);
        _tftService->setOrderRender(heating->getRender());

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

    TemperatureRender render;
    render.isNan = false;
    render.temperature = temperature;
    _tftService->setTemperatureRender(render);

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
    _receiverFactory->setState(false);

    TemperatureRender render;
    render.isNan = true;
    render.temperature = 99;
    _tftService->setTemperatureRender(render);

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
    } else {
        #ifdef DEBUG
            Serial.println("Error : Unkonw topic");
        #endif
        return;
    }

    _programme->setLastOrder(_programmeService->findCurrentOrder());
    _programme->setAnticipatingOrder(_programmeService->findAnticipatingOrder());

    Order *publishAnticipatingOrder = nullptr;
    if(_device->isProgrammeMode()) {
        publishAnticipatingOrder = _programme->getAnticipatingOrder();
    }

    String payload = _messageParserService->anticipatingToPayload(publishAnticipatingOrder);
    _mqttFactory->publish(_topicService->getAnticipating(), payload.c_str());

    Heating *heating = Heating::getMode(_device, _programme);
    bool regulationStatus = heating->regulationStatus(_dhtFactory->getTemperature());
    
    _receiverFactory->setState(regulationStatus);
    _tftService->setOrderRender(heating->getRender());

    delete heating;
}

void HeatingHandler::modeUpdated(Heating *heating)
{
    differedModeUpdatedTicker.detach();
    _tftService->setOrderRender(heating->getRender());
    delete heating;

    differedModeUpdatedTicker.once(2, std::bind(&HeatingHandler::differedModeUpdated, this));
}


void HeatingHandler::differedModeUpdated()
{
    String payload = _messageParserService->deviceToPayload(_device);
    _mqttFactory->publish(_topicService->getTemperatureControl(), payload.c_str());

    Order *publishAnticipatingOrder = nullptr;
    if(_device->isProgrammeMode()) {
        publishAnticipatingOrder = _programme->getAnticipatingOrder();
    }

    payload = _messageParserService->anticipatingToPayload(publishAnticipatingOrder);
    _mqttFactory->publish(_topicService->getAnticipating(), payload.c_str());

    Heating *heating = Heating::getMode(_device, _programme);

    bool regulationStatus = heating->regulationStatus(_dhtFactory->getTemperature());
    _receiverFactory->setState(regulationStatus);
    delete heating;
}