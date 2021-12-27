#ifndef T_TOPIC_SERVICE_H
#define T_TOPIC_SERVICE_H

#include <Arduino.h>

#include "Secret.h"


class TopicService {

public:
    TopicService(const char *deviceName);

    const char *getProgramme();
    const char *getDevice();
    const char *getTemperatures();
    const char *getHeating();
    const char *getTemperatureControl();
    const char *getAsker();
};

#endif