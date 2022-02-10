#include "TopicService.h"

TopicService::TopicService(const char *deviceName)
{

}

const char *TopicService::getProgramme()
{
    return MQTT_PROGRAMME_CHANNEL;
}

const char *TopicService::getDevice()
{
    return MQTT_DEVICE_CHANNEL;
}

const char *TopicService::getTemperatures()
{
    return MQTT_TEMPERATURES_CHANNEL;
}

const char *TopicService::getHeating()
{
    return MQTT_HEATING_CHANNEL;
}

const char *TopicService::getTemperatureControl()
{
    return MQTT_TEMPERATURE_CONTROL_CHANNEL;
}

const char *TopicService::getAsker()
{
    return MQTT_ASKER_CHANNEL;
}

const char *TopicService::getAnticipating()
{
    return MQTT_ANTICIPATING_CHANNEL;
}
