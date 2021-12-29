#include "DhtFactory.h"

DhtFactory::DhtFactory(unsigned short pin, unsigned short delay)
{
    _pin = pin;
    _delay = delay;
    _lastCheck = 0;
    _isNan = true;
    _dhtHandler = nullptr;
    _lastTemperature = 99;
    _tare = 0;
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
    
    // DEBUG
    float temperature;

    if(_lastTemperature == 21) {
        temperature = 20.5;
    } else {
        temperature = 21;
    }

    temperature = temperature + _tare;

    _isNan = false; 
    // gerer plusieurs echec de lecture avant de passer à isNan=true
    // _dhtHandler->temperatureIsNan();

    bool hasMuted = _lastTemperature != temperature;
    _lastTemperature = temperature;
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