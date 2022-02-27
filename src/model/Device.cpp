#include "Device.h"

Device::Device()
{
    _powerOn = false;
    _forced = true;
    _forcedTemperature = 20.6;
    _forcedUntil = -1;
    _brightnessMax = 100;
    _brightnessMin = 50;
    _heatingAnticipation = 0;
}

bool Device::isPowerOn()
{
    return _powerOn;
}

bool Device::isForced()
{
    return _powerOn && _forced;
}

bool Device::isForcedAlways()
{
    return _powerOn && _forced && _forcedUntil == -1;
}

bool Device::isForcedNextOrder()
{
    return _powerOn && _forced && _forcedUntil == 0;
}

bool Device::isForcedUntilDate()
{
    return _powerOn && _forced && _forcedUntil > 0;
}

bool Device::isProgrammeMode()
{
    return _powerOn && !_forced;
}

float Device::getForcedTemperature()
{
    return _forcedTemperature;
}

long Device::getForcedUntil()
{
    return _forcedUntil;
}

unsigned short Device::getBrightnessMax()
{
    return _brightnessMax;
}

unsigned short Device::getBrightnessMin()
{
    return _brightnessMin;
}

float Device::getHeatingAnticipation()
{
    return _heatingAnticipation;
}

void Device::setPowerOn(bool powerOn) 
{
    _powerOn = powerOn;
}

void Device::setForced(bool forced) 
{
    _forced = forced;
}

void Device::setForcedTemperature(float forcedTemperature) 
{
    _forcedTemperature = forcedTemperature;
}

void Device::setForcedUntil(long forcedUntil) 
{
    _forcedUntil = forcedUntil;
}

void Device::setBrightnessMax(unsigned short brightnessMax) 
{
    _brightnessMax = brightnessMax;
}

void Device::setBrightnessMin(unsigned short brightnessMin) 
{
    _brightnessMin = brightnessMin;
}

void Device::setHeatingAnticipation(float heatingAnticipation)
{
    _heatingAnticipation = heatingAnticipation;
}

