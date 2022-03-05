//
// Created by Romai on 20/12/2021.
//

#include "MessageParserService.h"

MessageParserService::MessageParserService(
    DhtFactory *dhtFactory
) {
    _dhtFactory = dhtFactory;
    _json_Capacity = 84*JSON_ARRAY_SIZE(3) + 3*JSON_ARRAY_SIZE(8) + JSON_ARRAY_SIZE(84) + JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(5) + 200;
}

String MessageParserService::deviceToPayload(Device *device)
{   
    String isForced = device->isForced() ? F("true") : F("false");
    String forcedTemperature = String(device->getForcedTemperature());
    String forcedUntil = String(device->getForcedUntil());
    String powerOn = device->isPowerOn() ? F("true") : F("false");

    String payload = F("{");
    payload += F("\"forced\":") + isForced + F(",");
    payload += F("\"forcedTemperature\":") + forcedTemperature + F(",");
    payload += F("\"forcedUntil\":") + forcedUntil + F(",");
    payload += F("\"powerOn\":") + powerOn;
    payload += F("}");

    return payload;
}

String MessageParserService::temperatureToPayload(float temperature, bool isNan)
{
    String temperatureStr = String(temperature);
    String isNanStr = isNan ? F("true") : F("false");
    String payload = F("{");
    payload += F("\"temperature\":") + temperatureStr + F(",");
    payload += F("\"nan\":") + isNanStr;
    payload += F("}");

    return payload; 
}

String MessageParserService::heatingToPayload(bool heating)
{
    String heatingStr = heating ? F("true") : F("false");

    String payload = F("{");
    payload += F("\"heating\":") + heatingStr;
    payload += F("}");

    return payload; 
}

String MessageParserService::anticipatingToPayload(Order *order)
{
    String anticipatingLabel = F("null");
    String anticipatingTemperature = F("0");
    if(order != nullptr) {
        anticipatingLabel = F("\"") + order->getLabel() + F("\"");
        anticipatingTemperature = String(order->getTemperature());
    }

    String payload = F("{");
    payload += F("\"anticipatingLabel\":") + anticipatingLabel + F(",");
    payload += F("\"anticipatingTemperature\":") + anticipatingTemperature;
    payload += F("}");

    return payload;
}

void MessageParserService::parseDevice(char *payload, Device *device)
{
    #ifdef DEBUG
        Serial.println(F("Parsing device payload"));
    #endif
    
    DynamicJsonDocument json(_json_Capacity);
    deserializeJson(json, payload);

    device->setBrightnessMin(json[F("brightnessMin")].as<unsigned short>());
    device->setBrightnessMax(json[F("brightnessMax")].as<unsigned short>());
    device->setForced(json[F("forced")].as<bool>());
    device->setPowerOn(json[F("powerOn")].as<bool>());
    device->setForcedTemperature(json[F("forcedTemperature")].as<float>());
    device->setForcedUntil(json[F("forcedUntil")].as<long>());
    device->setHeatingAnticipation(json[F("heatingAnticipation")].as<float>() / 60);

    Date::timezone = json[F("timezoneOffset")].as<int>();
    Date::summerTime = json[F("summerTime")].as<bool>();
    
    _dhtFactory->setTare(json[F("tareThermometer")].as<float>());
}

void MessageParserService::parseProgramme(char *payload, Programme *programme)
{
    //{"l":"Programme test","oi":[1,3,2],"ol":["Confort","test","Nuit"],"ot":[20.5,20.0,19.0],"ts":[[0,0,1],[0,60,2],[1,0,1],[1,60,2],[2,0,1],[2,60,2],[3,0,1],[3,60,2],[4,0,1],[4,60,2],[5,0,1],[5,60,2],[6,0,1],[6,60,2]]}
    #ifdef DEBUG
        Serial.println(F("Parsing programme payload"));
    #endif

    DynamicJsonDocument json(_json_Capacity);
    deserializeJson(json, payload);

    programme->setLabel(json[F("l")].as<String>());

    JsonArray ordersId = json[F("oi")].as<JsonArray>();
    JsonArray ordersLabel = json[F("ol")].as<JsonArray>();
    JsonArray ordersTemperature = json[F("ot")].as<JsonArray>();

    for(unsigned short i = 0; i < PROGRAMME_MAX_ORDERS; i++) {
        if (ordersId[i].isNull()) {
            programme->getOrder(i)->unused();
        } else {
            programme->getOrder(i)->update(
                ordersId[i].as<unsigned short>(),
                ordersLabel[i].as<String>(),
                ordersTemperature[i].as<float>()
            );
        }
    }

    JsonArray orderTimes = json[F("ts")].as<JsonArray>();
    for(unsigned short i = 0; i < PROGRAMME_MAX_TIMES_ORDERS; i++) {
        if(orderTimes[i].isNull()) {
            programme->getOrderTime(i)->unused();
        } else {
            programme->getOrderTime(i)->update(
                orderTimes[i][0].as<unsigned short>(),
                orderTimes[i][1].as<unsigned short>(),
                orderTimes[i][2].as<unsigned short>()
            );
        }
    }
}