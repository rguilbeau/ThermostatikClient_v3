#ifndef T_RECEIVER_H
#define T_RECEIVER_H

#include <Arduino.h>

#include "Debug.h"

#include <ESPAsyncWebServer.h>

#include "ReceiverStateHandlerInterface.h"
#include "ReceiverConnectionHandlerInterface.h"

class ReceiverFactory {

public:
    ReceiverFactory(
        String ssid, String password,
        int timeout,
        AsyncWebServer *server
    );

    void setConnectionHandler(ReceiverConnectionHandlerInterface *receiverConnectionHandler);
    void setStateHandler(ReceiverStateHandlerInterface *receiverStateHandler);

    void createAccessPoint();
    void setState(bool state);
    bool isConnected();

    bool getState();
    bool getReceiverState();

    void loop();

private:
    unsigned long _lastRequest;
    int _timeout;
    bool _connected;
    bool _state;
    bool _receiverState;

    String _ssid;
    String _password;
    AsyncWebServer *_server;
    IPAddress _ip;

    ReceiverConnectionHandlerInterface *_receiverConnectionHandler;
    ReceiverStateHandlerInterface *_receiverStateHandler;

    void onRequestReceiver(AsyncWebServerRequest *request);
};

#endif