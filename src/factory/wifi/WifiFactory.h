#ifdef ESP8266
    #include <ESP8266WiFi.h>
#else
    #include <WiFi.h>
#endif

#ifndef T_WIFI_FACTORY_H
#define T_WIFI_FACTORY_H

#include "Debug.h"

#include <Arduino.h>


#include "WifiConnectionHandlerInterface.h"

class WifiFactory {

public:    
    WifiFactory(String ssid, String password);

    void setHandler(WifiConnectionHandlerInterface *wifiHandler);
    void connect();
    bool isConnected();

private:
    String _ssid;
    String _password;

    #ifdef ESP8266
        void _onStationModeGotIP();
        void _onStationModeDisconnected();

        WiFiEventHandler _wifiConnectHandler;
        WiFiEventHandler _wifiDisconnectHandler;
    #endif

    WifiConnectionHandlerInterface *_wifiHandler;
};

#endif