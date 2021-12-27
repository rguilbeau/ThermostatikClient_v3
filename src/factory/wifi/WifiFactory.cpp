#include "WifiFactory.h"

WifiFactory::WifiFactory(String ssid, String password)
{
    _ssid = ssid;
    _password = password;
    _wifiHandler = nullptr;

    _wifiConnectHandler = WiFi.onStationModeGotIP(std::bind(&WifiFactory::_onStationModeGotIP, this));
    _wifiDisconnectHandler = WiFi.onStationModeDisconnected(std::bind(&WifiFactory::_onStationModeDisconnected, this));
}

void WifiFactory::setHandler(WifiConnectionHandlerInterface *wifiHandler)
{
    _wifiHandler = wifiHandler;
}

void WifiFactory::connect()
{
    #ifdef DEBUG
        Serial.print(F("Connect to wifi : "));
        Serial.println(_ssid);
    #endif
    WiFi.begin(_ssid, _password);
}

bool WifiFactory::isConnected()
{
    return WiFi.isConnected();
}

void WifiFactory::_onStationModeGotIP()
{
    #ifdef DEBUG
        Serial.println(F("Wifi connected"));
    #endif

    if(_wifiHandler != nullptr) {
        _wifiHandler->wifiConnected();
    }
}

void WifiFactory::_onStationModeDisconnected()
{
    #ifdef DEBUG
        Serial.println(F("Wifi disconnected"));
    #endif

    if(_wifiHandler != nullptr) {
        _wifiHandler->wifiDisconnected();
    }
}