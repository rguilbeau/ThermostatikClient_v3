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

    pinMode(_pin, INPUT);
    _dht->setup(_pin, DHTesp::DHT22);
}

void DhtFactory::setHandler(DhtHandlerInterface *dhtHandler)
{
    _dhtHandler = dhtHandler;
}

void DhtFactory::setTare(float tare)
{
    _tare = tare;
}

void DhtFactory::loop()
{
    bool hasMuted = false;

    if(_lastCheck + _delay < millis()) {
        hasMuted = _readTemperature();
        _lastCheck = millis();
    }

    if(isNan() && _dhtHandler != nullptr) {
        _dhtHandler->temperatureIsNan();
        hasMuted = false;
    }
    
    if(hasMuted) {
        #ifdef DEBUG
            Serial.print(F("DHT temperature muted : "));
            Serial.println(String(_lastTemperature));
        #endif

        if(_dhtHandler != nullptr) {
            _dhtHandler->temperatureChanged(_lastTemperature);
        }
    }
}

bool DhtFactory::_readTemperature()
{
    bool hasMuted = false;

    float temperature = fixDecimal(_dht->getTemperature() + _tare);
    _lastTemperature = _lastTemperature == 99 ? temperature : _lastTemperature; 

    if(_dht->getStatus() == 0 && !isnan(temperature)) {
        _isNanCnt = 0;
        
        float smoothTemperature = smooth(temperature, _lastTemperature, 0.16);
        hasMuted = smoothTemperature != _lastTemperature;
        _lastTemperature = smoothTemperature;
    } else {
        _isNanCnt += 1;
        hasMuted = false;
    }

    return hasMuted;
}

float DhtFactory::fixDecimal(float temperature)
{
    return round(temperature * 10) / 10;
}

float DhtFactory::smooth(float temperature, float lastSmoothTemperature, float factor)
{
    return fixDecimal((factor * temperature) + (1 - factor) * lastSmoothTemperature);
}

float DhtFactory::getTemperature()
{
    return _lastTemperature;
}

bool DhtFactory::isNan()
{
    return _isNanCnt >= 5;
}