#include "ReceiverFactory.h"
#include "ESP8266WiFi.h"

ReceiverFactory::ReceiverFactory(
    String ssid, String password, 
    int timeout,
    AsyncWebServer *server
) {
    _ssid = ssid;
    _password = password;
    _server = server;
    _timeout = timeout;
    _state = false;
    _receiverState = false;
    _lastRequest = 0;
    _connected = false;
}

void ReceiverFactory::createAccessPoint()
{
    #ifdef DEBUG
        Serial.println("Receiver : create access point");
    #endif

    WiFi.softAP(_ssid, _password);
    delay(100);
    
    _server->on("/state", HTTP_GET, std::bind(&ReceiverFactory::onRequestReceiver, this, std::placeholders::_1));
    _server->begin();
}

void ReceiverFactory::setConnectionHandler(ReceiverConnectionHandlerInterface *receiverConnectionHandler)
{
    _receiverConnectionHandler = receiverConnectionHandler;
}

void ReceiverFactory::setStateHandler(ReceiverStateHandlerInterface *receiverStateHandler)
{
    _receiverStateHandler = receiverStateHandler;
}

void ReceiverFactory::loop()
{
    bool isConnected = _lastRequest != 0 && ((_lastRequest + _timeout) > millis());

    if(_connected != isConnected) {
        _connected = isConnected;

        if(_receiverConnectionHandler != nullptr && _connected) {        
            _receiverConnectionHandler->receiverConnected();
        } else if(_receiverConnectionHandler != nullptr && !_connected) {
            _receiverConnectionHandler->receiverDisconnected();
        }
    }

    if(!_connected && _receiverState) {
        _receiverState = false;

        if(_receiverStateHandler != nullptr) {
            _receiverStateHandler->receiverStateChanged(_receiverState);
        }
    } 
}

void ReceiverFactory::setState(bool state)
{
    _state = state;
}

bool ReceiverFactory::getState()
{
    return _state;
}

bool ReceiverFactory::getReceiverState()
{
    return _receiverState;
}

bool ReceiverFactory::isConnected()
{
    return _connected;
}

void ReceiverFactory::onRequestReceiver(AsyncWebServerRequest *request)
{
    _lastRequest = millis();
    
    if(_state) {
        request->send(200, F("text/plain"), F("true"));
    } else {
        request->send(200, F("text/plain"), F("false"));
    }

    if(_receiverState != _state) {
        _receiverState = _state;

        if(_receiverStateHandler != nullptr) {
            _receiverStateHandler->receiverStateChanged(_receiverState);
        }
    }
}