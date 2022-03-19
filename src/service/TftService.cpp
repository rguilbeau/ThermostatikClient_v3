#include "TftService.h"

TftService::TftService (
    TftFactory *tftFactory
) {
    _tftFactory = tftFactory;

    ThermometerRender thermometerRender;
    _thermometerRender = thermometerRender;
    
    TemperatureRender temperatureRender;
    _temperatureRender = temperatureRender;

    TemperatureLabelRender temperatureLabelRender;
    _temperatureLabelRender = temperatureLabelRender;
    
    WifiStateRender wifiStateRender;
    _wifiStateRender = wifiStateRender;

    ServerStateRender serverStateRender;
    _serverStateRender = serverStateRender;

    ReceiverStateRender receiverStateRender;
    _receiverStateRender = receiverStateRender;

    OrderRender orderRender;
    _orderRender = orderRender;
    
    DateRender dateRender;
    _dateRender = dateRender;

    _isQuickRender = false;

    _thermometerRenderMutations = 1;
    _temperatureRenderMutations = 1;
    _temperatureLabelRenderMutations = 1;
    _wifiStateRenderMutations = 1;
    _serverStateRenderMutations = 1;
    _receiverStateRenderMutations = 1;
    _orderRenderMutations = 1;
    _dateRenderMutations = 1;
}

void TftService::loop()
{
    _printThermometerRender();
    _printTemperatureRender();
    _printTemperatureLabelRender();
    _printWifiStateRender();
    _printServerStateRender();
    _printReceiverStateRender();
    _printOrderRender();
    _printMessageRender();
    _isQuickRender = false;
}

void TftService::displayDefault()
{
    _tftFactory->fillRect(30, 105, 260, 2, TftColor::COLOR_GRAY);
    loop();
}

void TftService::setThermometerRender(ThermometerRender render) 
{
    _thermometerRender = render;
    _thermometerRenderMutations++;
}

void TftService::_printThermometerRender() 
{
    if(_thermometerRenderMutations > 0) {
        _tftFactory->draw(
            35, 15,
            _thermometerRender.image
        );
        _thermometerRenderMutations--;
    }
}

void TftService::setTemperatureRender(TemperatureRender render)
{
    _temperatureRender = render;
    _temperatureRenderMutations++;
}

void TftService::_printTemperatureRender() 
{
    if(_temperatureRenderMutations > 0) {
        TftText text;
        text.font = TftFont::LARGE;
        text.color = TftColor::COLOR_WHITE;
        text.width = 180;

        if(_temperatureRender.isNan) {
            text.text = F("--.- 'C");
        } else {
            text.text = TftFactory::formatTemperature(_temperatureRender.temperature);
        }

        _tftFactory->print(90, 20, text);
        _temperatureRenderMutations--;
    }
}

void TftService::setTemperatureLabelRender(TemperatureLabelRender render) 
{
    _temperatureLabelRender = render;
    _temperatureLabelRenderMutations++;
}

void TftService::_printTemperatureLabelRender() 
{
    if(_temperatureLabelRenderMutations > 0) {
        TftText text;
        text.font = TftFont::SMALL;
        text.color = TftColor::COLOR_GRAY;
        text.width = 180;
        text.text = _temperatureLabelRender.text;

        _tftFactory->print(90, 60, text);

        _temperatureLabelRenderMutations--;
    }
}

void TftService::setWifiStateRender(WifiStateRender render) 
{
    _wifiStateRender = render;
    _wifiStateRenderMutations++;
}

void TftService::_printWifiStateRender() 
{
    if(_wifiStateRenderMutations > 0) {
        if(_wifiStateRender.connected) {
            _tftFactory->fillRect(280, 10, 25, 25, TftColor::BG_DARK);
        } else {
            _tftFactory->draw(
                280, 10,
                TftImage::IMAGE_WIFI_OFF
            );
        }

        _wifiStateRenderMutations--;
    }
}

void TftService::setServerStateRender(ServerStateRender render) 
{
    _serverStateRender = render;
    _serverStateRenderMutations++;
}

void TftService::_printServerStateRender() 
{
    if(_serverStateRenderMutations > 0) {
        if(_serverStateRender.connected) {
            _tftFactory->fillRect(280, 40, 25, 25, TftColor::BG_DARK);
        } else {
            _tftFactory->draw(
                280, 40,
                TftImage::IMAGE_SERVER_OFF
            );
        }

        _serverStateRenderMutations--;
    }
}

void TftService::setReceiverStateRender(ReceiverStateRender render) 
{
    _receiverStateRender = render;
    _receiverStateRenderMutations++;
}

void TftService::_printReceiverStateRender() 
{
    if(_receiverStateRenderMutations > 0) {
        if(_receiverStateRender.connected) {
            _tftFactory->fillRect(280, 70, 25, 25, TftColor::BG_DARK);
        } else {
            _tftFactory->draw(
                280, 70,
                TftImage::IMAGE_RECEIVER_OFF
            );
        }

        _receiverStateRenderMutations--;
    }
}

void TftService::setOrderRender(OrderRender render) 
{
    Serial.println("set order render:" + render.temperature);
    _orderRender = render;
    _isQuickRender = false;
    _orderRenderMutations++;
}

void TftService::setOrderRender(OrderRender render, bool isQuickRender) 
{
    _orderRender = render;
    _isQuickRender = isQuickRender;
    _orderRenderMutations++;
}

void TftService::_printOrderRender() 
{   
    if(_orderRenderMutations > 0) {
        Serial.println("==> " + _orderRender.temperature);
        _tftFactory->draw(30, 125, _orderRender.icon);

        TftText temperatureText;
        temperatureText.font = TftFont::LARGE;
        temperatureText.color = TftColor::COLOR_WHITE;
        temperatureText.width = 150;
        temperatureText.text = _orderRender.temperature;
        _tftFactory->print(90, 125, temperatureText);

        if(!_isQuickRender) {
            TftText labelText;
            labelText.font = TftFont::SMALL;
            labelText.color = TftColor::COLOR_GRAY;
            labelText.width = 200;
            labelText.text = _orderRender.label;
            _tftFactory->print(90, 165, labelText);

            TftText infoText;
            infoText.font = TftFont::SMALL;
            infoText.color = TftColor::COLOR_GRAY;
            infoText.width = 200;
            infoText.text = _orderRender.info;
            _tftFactory->print(90, 185, infoText);
        }

        _orderRenderMutations--;
        Serial.println("order printed");
    }
}

void TftService::setMessageRender(DateRender render) 
{
    _dateRender = render;
    _dateRenderMutations++;
}

void TftService::_printMessageRender() 
{
    if(_dateRenderMutations > 0) {
        TftText date;
        date.font = TftFont::SMALL;
        date.color = TftColor::COLOR_WHITE;
        date.width = 250;
        date.text = _dateRender.date;
        _tftFactory->print(20, 220, date);

        _dateRenderMutations--;
    }
}