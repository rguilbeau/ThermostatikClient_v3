#include "TemperatureSensorFactory.h"

TemperatureSensorFactory::TemperatureSensorFactory(SHT31 *sht, uint8_t i2cAdrr, unsigned short delay)
{
    _sht = sht;
    _delay = delay;
    _lastCheck = 0;
    _temperatureSensorHandler = nullptr;
    _lastTemperature = 99;
    _tare = 0;
    _nanNotified = false;
    _isNanCnt = 0;
    _isNan = true;
    pinMode(_pin, INPUT);
    _sht->begin(i2cAdrr);
}

void TemperatureSensorFactory::setHandler(TemperatureSensorHandlerInterface *temperatureSensorHandler)
{
    _temperatureSensorHandler = temperatureSensorHandler;
}

void TemperatureSensorFactory::setSmoother(TemperatureSmootherInterface *temperatureSmoother)
{
    _temperatureSmoother = temperatureSmoother;
}

void TemperatureSensorFactory::setTare(float tare)
{
    _tare = tare;
}

void TemperatureSensorFactory::loop()
{
    bool hasMuted = false;

    if(_lastCheck + _delay < millis()) {
        _lastCheck = millis();
        
        hasMuted = _readTemperature();

        if(isNan()) {
            hasMuted = false;

            if(!_nanNotified && _temperatureSensorHandler != nullptr) {
                _temperatureSensorHandler->temperatureIsNan();
                _nanNotified = true;
            }
        }

        if(hasMuted) {
            #ifdef DEBUG
                Serial.print(F("Temperature muted (with tare): "));
                Serial.println(String(getTemperature()));
            #endif
            _nanNotified = false;

            if(_temperatureSensorHandler != nullptr) {
                _temperatureSensorHandler->temperatureChanged(getTemperature());
            }
        }
    }
}

bool TemperatureSensorFactory::_readTemperature()
{
    bool hasMuted = false;

    _sht->read();
    float temperature = _sht->getTemperature() + _tare;

    if(_sht->getError() == SHT31_OK && !isnan(temperature)) {
        _isNanCnt = 0;

        if(_lastTemperature == 99) {
            _lastTemperature = temperature;
            hasMuted = true;
        }

        if(_temperatureSmoother != nullptr) {
            temperature = _temperatureSmoother->smooth(temperature, _lastTemperature);
        }

        hasMuted = hasMuted || _lastTemperature != temperature;
        _lastTemperature = temperature;
    } else {
        #ifdef DEBUG
            Serial.print(F("Temperaure is nan. count nan:"));
            Serial.println(String(_isNanCnt));
        #endif
        _isNanCnt += 1;
    }

    _isNan = _isNanCnt > 4;
    return hasMuted;
}

float TemperatureSensorFactory::getTemperature()
{
    return _lastTemperature;
}

bool TemperatureSensorFactory::isNan()
{
    return _isNan;
}