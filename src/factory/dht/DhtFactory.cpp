#include "DhtFactory.h"

DhtFactory::DhtFactory(DHTesp *dht, unsigned short pin, unsigned short delay)
{
    _dht = dht;
    _pin = pin;
    _delay = delay;
    _lastCheck = 0;
    _dhtHandler = nullptr;
    _lastTemperature = 99;
    _tare = 0;
    _nanNotified = false;
    _isNanCnt = 0;
    _isNan = true;
    pinMode(_pin, INPUT);
    _dht->setup(_pin, DHTesp::DHT22);
}

void DhtFactory::setHandler(DhtHandlerInterface *dhtHandler)
{
    _dhtHandler = dhtHandler;
}

void DhtFactory::setSmoother(DhtSmootherInterface *dhtSmoother)
{
    _dhtSmoother = dhtSmoother;
}

void DhtFactory::setTare(float tare)
{
    _tare = tare;
}

void DhtFactory::loop()
{
    bool hasMuted = false;

    if(_lastCheck + _delay < millis()) {
        _lastCheck = millis();
        
        hasMuted = _readTemperature();

        if(isNan()) {
            hasMuted = false;

            if(!_nanNotified && _dhtHandler != nullptr) {
                _dhtHandler->temperatureIsNan();
                _nanNotified = true;
            }
        }

        if(hasMuted) {
            #ifdef DEBUG
                Serial.print(F("DHT temperature muted (with tare): "));
                Serial.println(String(getTemperature()));
            #endif
            _nanNotified = false;

            if(_dhtHandler != nullptr) {
                _dhtHandler->temperatureChanged(getTemperature());
            }
        }
    }
}

bool DhtFactory::_readTemperature()
{
    bool hasMuted = false;

    float temperature = _dht->getTemperature() + _tare;

    if(_dht->getStatus() == 0 && !isnan(temperature)) {
        _isNanCnt = 0;

        if(_lastTemperature == 99) {
            _lastTemperature = temperature;
            hasMuted = true;
        }

        if(_dhtSmoother != nullptr) {
            temperature = _dhtSmoother->smooth(temperature, _lastTemperature);
        }

        hasMuted = hasMuted || _lastTemperature != temperature;
        _lastTemperature = temperature;
    } else {
        #ifdef DEBUG
            Serial.print(F("DHT temperaure is nan. count nan:"));
            Serial.println(String(_isNanCnt));
        #endif
        _isNanCnt += 1;
    }

    _isNan = _isNanCnt > 4;
    return hasMuted;
}

float DhtFactory::getTemperature()
{
    return _lastTemperature;
}

bool DhtFactory::isNan()
{
    return _isNan;
}