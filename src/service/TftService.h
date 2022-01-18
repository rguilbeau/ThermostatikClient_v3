#ifndef T_TFT_SERVICE_H
#define T_TFT_SERVICE_H

#include "factory/tft/TftFactory.h"
#include "render/MessageRender.h"
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

    void setThermometerRender(ThermometerRender render);
    void setTemperatureRender(TemperatureRender render);
    void setTemperatureLabelRender(TemperatureLabelRender render);
    void setWifiStateRender(WifiStateRender render);
    void setServerStateRender(ServerStateRender render);
    void setReceiverStateRender(ReceiverStateRender render);
    void setOrderRender(OrderRender render);
    void setMessageRender(MessageRender render);

private:
    TftFactory *_tftFactory;
};

#endif