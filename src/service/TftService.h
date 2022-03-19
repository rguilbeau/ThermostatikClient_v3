#ifndef T_TFT_SERVICE_H
#define T_TFT_SERVICE_H

#include <Arduino.h>

#include "factory/tft/TftFactory.h"
#include "render/DateRender.h"
#include "render/OrderRender.h"
#include "render/ReceiverStateRender.h"
#include "render/ServerStateRender.h"
#include "render/TemperatureLabelRender.h"
#include "render/TemperatureRender.h"
#include "render/ThermometerRender.h"
#include "render/WifiStateRender.h"

class TftService {

public:
    TftService(
        TftFactory *tftFactory
    );

    void loop();

    void displayDefault();
    
    void setThermometerRender(ThermometerRender render);
    void setTemperatureRender(TemperatureRender render);
    void setTemperatureLabelRender(TemperatureLabelRender render);
    void setWifiStateRender(WifiStateRender render);
    void setServerStateRender(ServerStateRender render);
    void setReceiverStateRender(ReceiverStateRender render);
    void setOrderRender(OrderRender render);
    void setOrderRender(OrderRender render, bool isQuickRender);
    void setMessageRender(DateRender render);

private:
    TftFactory *_tftFactory;

    ThermometerRender _thermometerRender;
    TemperatureRender _temperatureRender;
    TemperatureLabelRender _temperatureLabelRender;
    WifiStateRender _wifiStateRender;
    ServerStateRender _serverStateRender;
    ReceiverStateRender _receiverStateRender;
    OrderRender _orderRender;
    DateRender _dateRender;
    bool _isQuickRender;

    short _thermometerRenderMutations;
    short _temperatureRenderMutations;
    short _temperatureLabelRenderMutations;
    short _wifiStateRenderMutations;
    short _serverStateRenderMutations;
    short _receiverStateRenderMutations;
    short _orderRenderMutations;
    short _dateRenderMutations;

    void _printThermometerRender();
    void _printTemperatureRender();
    void _printTemperatureLabelRender();
    void _printWifiStateRender();
    void _printServerStateRender();
    void _printReceiverStateRender();
    void _printOrderRender();
    void _printMessageRender();
};

#endif