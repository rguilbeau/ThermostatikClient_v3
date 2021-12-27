#ifndef T_WIFI_FACTORY_H
#define T_WIFI_FACTORY_H

#include "Debug.h"

#include <Arduino.h>
#include <ESP8266WiFi.h>

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

    void _onStationModeGotIP();
    void _onStationModeDisconnected();

    WiFiEventHandler _wifiConnectHandler;
    WiFiEventHandler _wifiDisconnectHandler;

    WifiConnectionHandlerInterface *_wifiHandler;
};

#endif