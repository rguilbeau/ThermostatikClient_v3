#include "TftService.h"

TftService::TftService (
    TftFactory *tftFactory
) {
    _tftFactory = tftFactory;

    _thermometerRender = nullptr;
    _temperatureRender = nullptr;
    _temperatureLabelRender = nullptr;
    _wifiStateRender = nullptr;
    _serverStateRender = nullptr;
    _receiverStateRender = nullptr;
    _orderRender = nullptr;
    _dateRender = nullptr;
    _isQuickRender = false;
}

void TftService::loop()
{

    if(_thermometerRender != nullptr) {
        _printThermometerRender();
        delete _thermometerRender;
    }

    if(_temperatureRender != nullptr) {
        _printTemperatureRender();
        delete _temperatureRender;
    }

    if(_temperatureLabelRender != nullptr) {
        _printTemperatureLabelRender();
        delete _temperatureLabelRender;
    }

    if(_wifiStateRender != nullptr) {
        _printWifiStateRender();
        delete _wifiStateRender;
    }

    if(_serverStateRender != nullptr) {
        _printServerStateRender();
        delete _serverStateRender;
    }

    if(_receiverStateRender != nullptr) {
        _printReceiverStateRender();
        delete _receiverStateRender;
    }

    if(_orderRender != nullptr) {
        _printOrderRender();
        delete _orderRender;
    }

    if(_dateRender != nullptr) {
        _printMessageRender();
        delete _dateRender;
    }

    _isQuickRender = false;
}

void TftService::displayDefault()
{
    _thermometerRender = new ThermometerRender();
    _temperatureRender = new TemperatureRender();
    _temperatureLabelRender = new TemperatureLabelRender();
    _receiverStateRender = new ReceiverStateRender();
    _serverStateRender = new ServerStateRender();
    _wifiStateRender = new WifiStateRender();
    _orderRender = new OrderRender();
    _dateRender = new DateRender();

    _tftFactory->fillRect(30, 105, 260, 2, TftColor::COLOR_GRAY);
    loop();
}

void TftService::setThermometerRender(ThermometerRender render) 
{
    delete _thermometerRender;
    _thermometerRender = &render;
}

void TftService::_printThermometerRender() 
{
    _tftFactory->draw(
        35, 15,
        _thermometerRender->image
    );
}

void TftService::setTemperatureRender(TemperatureRender render)
{
    delete _temperatureRender;
    _temperatureRender = &render;
}

void TftService::_printTemperatureRender() 
{
    TftText text;
    text.font = TftFont::LARGE;
    text.color = TftColor::COLOR_WHITE;
    text.width = 180;

    if(_temperatureRender->isNan) {
        text.text = F("--.- 'C");
    } else {
        text.text = TftFactory::formatTemperature(_temperatureRender->temperature);
    }

    _tftFactory->print(90, 20, text);
}

void TftService::setTemperatureLabelRender(TemperatureLabelRender render) 
{
    delete _temperatureLabelRender;
    _temperatureLabelRender = &render;
}

void TftService::_printTemperatureLabelRender() 
{
    TftText text;
    text.font = TftFont::SMALL;
    text.color = TftColor::COLOR_GRAY;
    text.width = 180;
    text.text = _temperatureLabelRender->text;

    _tftFactory->print(90, 60, text);
}

void TftService::setWifiStateRender(WifiStateRender render) 
{
    delete _wifiStateRender;
    _wifiStateRender = &render;
}

void TftService::_printWifiStateRender() 
{
    if(_wifiStateRender->connected) {
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
    delete _serverStateRender;
    _serverStateRender = &render;
}

void TftService::_printServerStateRender() 
{
    if(_serverStateRender->connected) {
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
    delete _receiverStateRender;
    _receiverStateRender = &render;
}

void TftService::_printReceiverStateRender() 
{
    if(_receiverStateRender->connected) {
        _tftFactory->fillRect(280, 70, 25, 25, TftColor::BG_DARK);
    } else {
        _tftFactory->draw(
            280, 70,
            TftImage::IMAGE_RECEIVER_OFF
        );
    }
}

void TftService::setOrderRender(OrderRender render) 
{
    delete _orderRender;
    _orderRender = &render;
    _isQuickRender = false;
}

void TftService::setOrderRender(OrderRender render, bool isQuickRender) 
{
    delete _orderRender;
    _orderRender = &render;
    _isQuickRender = isQuickRender;
}

void TftService::_printOrderRender() 
{
    _tftFactory->draw(30, 125, _orderRender->icon);

    TftText temperatureText;
    temperatureText.font = TftFont::LARGE;
    temperatureText.color = TftColor::COLOR_WHITE;
    temperatureText.width = 150;
    temperatureText.text = _orderRender->temperature;
    _tftFactory->print(90, 125, temperatureText);

    if(!_isQuickRender) {
        TftText labelText;
        labelText.font = TftFont::SMALL;
        labelText.color = TftColor::COLOR_GRAY;
        labelText.width = 200;
        labelText.text = _orderRender->label;
        _tftFactory->print(90, 165, labelText);

        TftText infoText;
        infoText.font = TftFont::SMALL;
        infoText.color = TftColor::COLOR_GRAY;
        infoText.width = 200;
        infoText.text = _orderRender->info;
        _tftFactory->print(90, 185, infoText);
    }
}

void TftService::setMessageRender(DateRender render) 
{
    delete _dateRender;
    _dateRender = &render;
}

void TftService::_printMessageRender() 
{
    TftText date;
    date.font = TftFont::SMALL;
    date.color = TftColor::COLOR_WHITE;
    date.width = 250;
    date.text = _dateRender->date;
    _tftFactory->print(20, 220, date);
}