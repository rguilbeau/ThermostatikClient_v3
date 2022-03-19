#include "WifiFactory.h"

WifiFactory::WifiFactory(String ssid, String password)
{
    _ssid = ssid;
    _password = password;
    _wifiHandler = nullptr;

    #ifdef ESP8266
        _wifiConnectHandler = WiFi.onStationModeGotIP(std::bind(&WifiFactory::_onStationModeGotIP, this));
        _wifiDisconnectHandler = WiFi.onStationModeDisconnected(std::bind(&WifiFactory::_onStationModeDisconnected, this));

    #else

        WiFi.onEvent([&](WiFiEvent_t event, WiFiEventInfo_t info){            
            #ifdef DEBUG
                Serial.println(F("Wifi connected"));
            #endif

            if(_wifiHandler != nullptr) {
                _wifiHandler->wifiConnected();
            }
        }, WiFiEvent_t::SYSTEM_EVENT_STA_GOT_IP);


        WiFi.onEvent([&](WiFiEvent_t event, WiFiEventInfo_t info){            
            #ifdef DEBUG
                Serial.println(F("Wifi disconnected"));
            #endif

            if(_wifiHandler != nullptr) {
                _wifiHandler->wifiDisconnected();
            }
        }, WiFiEvent_t::SYSTEM_EVENT_STA_DISCONNECTED);
    #endif
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

    #ifdef ESP8266
        WiFi.begin(_ssid, _password);
    #else
        WiFi.begin(_ssid.c_str(), _password.c_str());
    #endif
}

bool WifiFactory::isConnected()
{
    return WiFi.isConnected();
}

#ifdef ESP8266
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
#endif