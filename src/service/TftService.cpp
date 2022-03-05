#include "TftService.h"

TftService::TftService (
    TftFactory *tftFactory
) {
    _tftFactory = tftFactory;
}

void TftService::displayDefault()
{
    ThermometerRender thermometerRender;
    TemperatureRender temperatureRender;
    TemperatureLabelRender temperatureLabelRender;
    ReceiverStateRender receiverStateRender;
    ServerStateRender serverStateRender;
    WifiStateRender wifiStateRender;
    OrderRender orderRender;
    DateRender render;

    setThermometerRender(thermometerRender);
    setTemperatureRender(temperatureRender);
    setTemperatureLabelRender(temperatureLabelRender);
    setReceiverStateRender(receiverStateRender);
    setServerStateRender(serverStateRender);
    setWifiStateRender(wifiStateRender);
    setOrderRender(orderRender);
    setMessageRender(render);

    _tftFactory->fillRect(30, 105, 260, 2, TftColor::COLOR_GRAY);
}

void TftService::setThermometerRender(ThermometerRender render) 
{
    _tftFactory->draw(
        35, 15,
        render.image
    );
}

void TftService::setTemperatureRender(TemperatureRender render) 
{
    TftText text;
    text.font = TftFont::LARGE;
    text.color = TftColor::COLOR_WHITE;
    text.width = 180;

    if(render.isNan) {
        text.text = F("--.- 'C");
    } else {
        text.text = TftFactory::formatTemperature(render.temperature);
    }

    _tftFactory->print(90, 20, text);
}

void TftService::setTemperatureLabelRender(TemperatureLabelRender render) 
{
    TftText text;
    text.font = TftFont::SMALL;
    text.color = TftColor::COLOR_GRAY;
    text.width = 180;
    text.text = render.text;

    _tftFactory->print(90, 60, text);
}

void TftService::setWifiStateRender(WifiStateRender render) 
{
    if(render.connected) {
        _tftFactory->fillRect(280, 10, 25, 25, TftColor::BG_DARK);
    } else {
        _tftFactory->draw(
            280, 10,
            TftImage::IMAGE_WIFI_OFF
        );
    }
}

void TftService::setServerStateRender(ServerStateRender render) 
{
    if(render.connected) {
        _tftFactory->fillRect(280, 40, 25, 25, TftColor::BG_DARK);
    } else {
        _tftFactory->draw(
            280, 40,
            TftImage::IMAGE_SERVER_OFF
        );
    }
}

void TftService::setReceiverStateRender(ReceiverStateRender render) 
{
    if(render.connected) {
        _tftFactory->fillRect(280, 70, 25, 25, TftColor::BG_DARK);
    } else {
        _tftFactory->draw(
            280, 70,
            TftImage::IMAGE_RECEIVER_OFF
        );
    }
}

void TftService::setOrderRender(OrderRender render) {
    setOrderRender(render, false);
}

void TftService::setOrderRender(OrderRender render, bool isQuickRender) 
{
    _tftFactory->draw(30, 125, render.icon);

    TftText temperatureText;
    temperatureText.font = TftFont::LARGE;
    temperatureText.color = TftColor::COLOR_WHITE;
    temperatureText.width = 150;
    temperatureText.text = render.temperature;
    _tftFactory->print(90, 125, temperatureText);

    if(!isQuickRender) {
        TftText labelText;
        labelText.font = TftFont::SMALL;
        labelText.color = TftColor::COLOR_GRAY;
        labelText.width = 200;
        labelText.text = render.label;
        _tftFactory->print(90, 165, labelText);

        TftText infoText;
        infoText.font = TftFont::SMALL;
        infoText.color = TftColor::COLOR_GRAY;
        infoText.width = 200;
        infoText.text = render.info;
        _tftFactory->print(90, 185, infoText);
    }
}

void TftService::setMessageRender(DateRender render) 
{
    TftText date;
    date.font = TftFont::SMALL;
    date.color = TftColor::COLOR_WHITE;
    date.width = 250;
    date.text = render.date;
    _tftFactory->print(20, 220, date);
}