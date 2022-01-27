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
    String isForced = device->isForced() ? "true" : "false";
    String forcedTemperature = String(device->getForcedTemperature());
    String forcedUntil = String(device->getForcedUntil());
    String powerOn = device->isPowerOn() ? "true" : "false";

    String payload = "{";
    payload += "\"forced\":" + isForced + ",";
    payload += "\"forcedTemperature\":" + forcedTemperature + ",";
    payload += "\"forcedUntil\":" + forcedUntil + ",";
    payload += "\"powerOn\":" + powerOn;
    payload += "}";

    return payload;
}

String MessageParserService::temperatureToPayload(float temperature, bool isNan)
{
    if(isNan) {
        // pas de gestion is nan côté server...
        temperature = 99;
    }

    String temperatureStr = String(temperature);

    String payload = "{";
    payload += "\"temperature\":" + temperatureStr;
    payload += "}";

    return payload; 
}

String MessageParserService::heatingToPayload(bool heating)
{
    String heatingStr = heating ? "true" : "false";

    String payload = "{";
    payload += "\"heating\":" + heatingStr;
    payload += "}";

    return payload; 
}

void MessageParserService::parseDevice(char *payload, Device *device)
{
    #ifdef DEBUG
        Serial.println("Parsing device payload");
    #endif
    
    DynamicJsonDocument json(_json_Capacity);
    deserializeJson(json, payload);

    device->setBrightnessMin(json["brightnessMin"].as<unsigned short>());
    device->setBrightnessMax(json["brightnessMax"].as<unsigned short>());
    device->setForced(json["forced"].as<bool>());
    device->setPowerOn(json["powerOn"].as<bool>());
    device->setForcedTemperature(json["forcedTemperature"].as<float>());
    device->setForcedUntil(json["forcedUntil"].as<long>());
    device->setHeatingAnticipation(json["heatingAnticipation"].as<unsigned short>());

    Date::timezone = json["timezoneOffset"].as<int>();
    Date::summerTime = json["summerTime"].as<bool>();
    
    _dhtFactory->setTare(json["tareThermometer"].as<float>());
}

void MessageParserService::parseProgramme(char *payload, Programme *programme)
{
    //{"l":"Programme test","oi":[1,3,2],"ol":["Confort","test","Nuit"],"ot":[20.5,20.0,19.0],"ts":[[0,0,1],[0,60,2],[1,0,1],[1,60,2],[2,0,1],[2,60,2],[3,0,1],[3,60,2],[4,0,1],[4,60,2],[5,0,1],[5,60,2],[6,0,1],[6,60,2]]}
    #ifdef DEBUG
        Serial.println("Parsing programme payload");
    #endif

    DynamicJsonDocument json(_json_Capacity);
    deserializeJson(json, payload);

    programme->setLabel(json["l"].as<String>());

    JsonArray ordersId = json["oi"].as<JsonArray>();
    JsonArray ordersLabel = json["ol"].as<JsonArray>();
    JsonArray ordersTemperature = json["ot"].as<JsonArray>();

    for(int i = 0; i < PROGRAMME_MAX_ORDERS; i++) {
        if (ordersId[i].isNull()) {
            programme->getOrder(i)->unused();
        } else {
            programme->getOrder(i)->update(
                ordersId[i].as<int>(),
                ordersLabel[i].as<String>(),
                ordersTemperature[i].as<float>()
            );
        }
    }

    JsonArray orderTimes = json["ts"].as<JsonArray>();
    for(int i = 0; i < PROGRAMME_MAX_TIMES_ORDERS; i++) {
        if(orderTimes[i].isNull()) {
            programme->getOrderTime(i)->unused();
        } else {
            programme->getOrderTime(i)->update(
                orderTimes[i][0].as<int>(),
                orderTimes[i][1].as<int>(),
                orderTimes[i][2].as<int>()
            );
        }
    }
}