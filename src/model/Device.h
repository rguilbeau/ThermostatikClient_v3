#ifndef T_DEVICE_H
#define T_DEVICE_H

#include <Arduino.h>

class Device {

public:

    Device();

    bool isPowerOn();
    bool isForced();
    bool isForcedAlways();
    bool isForcedNextOrder();
    bool isForcedUntilDate();
    bool isProgrammeMode();
    float getForcedTemperature();
    long getForcedUntil();
    unsigned short getBrightnessMax();
    unsigned short getBrightnessMin();
    float getHeatingAnticipation();

    void setPowerOn(bool powerOn);
    void setForced(bool forced);
    void setForcedTemperature(float forcedTemperature);
    void setForcedUntil(long forcedUntil);
    void setBrightnessMax(unsigned short brightnessMax);
    void setBrightnessMin(unsigned short brightnessMin);
    void setHeatingAnticipation(float heatingAnticipation);

private:
    bool _powerOn;
    bool _forced;
    float _forcedTemperature;
    long _forcedUntil;
    unsigned short _brightnessMax;
    unsigned short _brightnessMin;
    float _heatingAnticipation;
};

#endif