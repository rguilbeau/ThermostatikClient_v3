//
// Created by Romai on 20/12/2021.
//

#ifndef THERMOSTATIKCLIENT_V3_PROGRAMMEPARSERSERVICE_H
#define THERMOSTATIKCLIENT_V3_PROGRAMMEPARSERSERVICE_H

#include <Arduino.h>

#include <ArduinoJson.h>

#include "Debug.h"

#include "factory/dht/DhtFactory.h"

#include "utils/Date.h"

#include "model/Programme.h"
#include "model/Order.h"
#include "model/OrderTime.h"
#include "model/Device.h"

class MessageParserService {

public:

    MessageParserService(
        DhtFactory *dhtFactory
    );

    void parseDevice(char *payload, Device *device);
    void parseProgramme(char *payload, Programme *programme);

    String deviceToPayload(Device *device);
    String temperatureToPayload(float temperature, bool isNan);
    String heatingToPayload(bool heating);
    
private:
    DhtFactory *_dhtFactory;
    size_t _json_Capacity;

};


#endif //THERMOSTATIKCLIENT_V3_PROGRAMMEPARSERSERVICE_H
