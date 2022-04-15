#include "TemperatureSmootherHandler.h"

TemperatureSmootherHandler::TemperatureSmootherHandler()
{
    _readsIndex = -1;
    _lastTemperature = 0;
}

float TemperatureSmootherHandler::smooth(float temperature, float lastTemperature)
{
    temperature = fixDecimal(temperature);
    _lastTemperature = fixDecimal(lastTemperature);

    if(_readsIndex == -1) {
        _reads[0] = temperature;
        _reads[1] = temperature;
        _reads[2] = temperature;
        _readsIndex = 3;
    } else {
        _reads[_readsIndex] = temperature;
        _readsIndex++;
    }

    if(_readsIndex == 3) {
        _readsIndex = 0;
        sort(_reads, 3);
        float medianTemperature = _reads[1];

        float smoothTemperature = smooth(medianTemperature, lastTemperature, 0.45);
        _lastTemperature = smoothTemperature;

        if(_lastTemperature != smoothTemperature) {
            #ifdef DEBUG
                Serial.print(F("Temperature smoother reads["));
                Serial.print(String(_reads[0]));
                Serial.print(F(", "));
                Serial.print(String(_reads[1]));
                Serial.print(F(", "));
                Serial.print(String(_reads[2]));
                Serial.print(F("] median:"));
                Serial.print(String(medianTemperature));
                Serial.print(F(", smooth:"));
                Serial.print(String(smoothTemperature));
                Serial.print(F(", last:"));
                Serial.println(String(lastTemperature));
            #endif
        }

        _lastTemperature = smoothTemperature;
    }

    return _lastTemperature;
}

void TemperatureSmootherHandler::sort(float a[], unsigned short size)
{
    for(int i=0; i<(size-1); i++) {
        for(int o=0; o<(size-(i+1)); o++) {
            if(a[o] > a[o+1]) {
                float t = a[o];
                a[o] = a[o+1];
                a[o+1] = t;
            }
        }
    }
}

float TemperatureSmootherHandler::smooth(float temperature, float lastTemperature, float factor)
{
    return fixDecimal((factor * temperature) + (1 - factor) * lastTemperature);
}

float TemperatureSmootherHandler::fixDecimal(float temperature)
{
    return round(temperature * 10) / 10;
}