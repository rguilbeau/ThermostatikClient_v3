#include "TftService.h"

TftService::TftService (
    TftFactory *tftFactory,
    TftDateHandler *tftDateHandler
) {
    _tftFactory = tftFactory;
    _tftDateHandler = tftDateHandler;
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
    
    setThermometerRender(thermometerRender);
    setTemperatureRender(temperatureRender);
    setTemperatureLabelRender(temperatureLabelRender);
    setReceiverStateRender(receiverStateRender);
    setServerStateRender(serverStateRender);
    setWifiStateRender(wifiStateRender);
    setOrderRender(orderRender);
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
        text.text = "--.- 'C";
    } else {
        text.text = TftFactory::formatTemperature(render.temperature);
    }

    _tftFactory->print(85, 20, text);
}

void TftService::setTemperatureLabelRender(TemperatureLabelRender render) 
{
    TftText text;
    text.font = TftFont::SMALL;
    text.color = TftColor::COLOR_GRAY;
    text.width = 180;
    text.text = render.text;

    _tftFactory->print(85, 60, text);
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
        _tftFactory->fillRect(280, 10, 25, 25, TftColor::BG_DARK);
    } else {
        _tftFactory->draw(
            280, 10,
            TftImage::IMAGE_SERVER_OFF
        );
    }
}

void TftService::setReceiverStateRender(ReceiverStateRender render) 
{
    if(render.connected) {
        _tftFactory->fillRect(280, 10, 25, 25, TftColor::BG_DARK);
    } else {
        _tftFactory->draw(
            280, 10,
            TftImage::IMAGE_RECEIVER_OFF
        );
    }
}

void TftService::setOrderRender(OrderRender render) 
{
    _tftFactory->draw(30, 125, render.icon);

    TftText temperatureText;
    temperatureText.font = TftFont::LARGE;
    temperatureText.color = TftColor::COLOR_WHITE;
    temperatureText.width = 200;
    temperatureText.text = render.temperature;
    _tftFactory->print(85, 125, temperatureText);

    TftText labelText;
    labelText.font = TftFont::SMALL;
    labelText.color = TftColor::COLOR_WHITE;
    labelText.width = 200;
    labelText.text = render.label;
    _tftFactory->print(85, 125, labelText);

    TftText infoText;
    infoText.font = TftFont::SMALL;
    infoText.color = TftColor::COLOR_WHITE;
    infoText.width = 200;
    infoText.text = render.info;
    _tftFactory->print(85, 125, infoText);
}

void TftService::message(String message)
{
    if(message == "") {
        _tftDateHandler->enable();
        _tftDateHandler->clockHandle();
    } else {
        _tftDateHandler->disable();
        MessageRender render;
        render.message = message; 
        setMessageRender(render);
    }
}

void TftService::setMessageRender(MessageRender render) 
{
    TftText message;
    message.font = TftFont::SMALL;
    message.color = TftColor::COLOR_WHITE;
    message.width = 250;
    
    if(render.message != "") {
        message.text = render.message;
    } else {
        message.text = render.date.toLongFormat();
    }

    _tftFactory->print(20, 220, message);
}