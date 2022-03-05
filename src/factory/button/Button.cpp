#include "Button.h"

Button::Button(uint8_t pin, ButtonType buttonType, unsigned short debounce)
{
    _pin = pin;
    _buttonType = buttonType;
    _pushed = false;
    _debounce = debounce;
    _lastCheck = 0;
}

void Button::setHandler(ButtonHandlerInterface *handler)
{
    pinMode(_pin, INPUT_PULLUP);
    _handler = handler;
}

void Button::loop()
{
    unsigned long currentMillis = millis();

    if(_lastCheck + _debounce < currentMillis) {
        bool current = digitalRead(_pin) == LOW;

        if(!_pushed && current) {
            _pushed = true;
        } else if(_pushed && !current) {
            _handler->pushed(_buttonType, getTypeStr());
            _pushed = false;
        }

        _lastCheck = currentMillis;
    }
}

ButtonType Button::getType()
{
    return _buttonType;
}

String Button::getTypeStr()
{
    String type;
    switch (_buttonType) {
        case BUTTON_OK:
            type = F("OK");
            break;
        case BUTTON_MORE:
            type = F("MORE");
            break;
        case BUTTON_MINUS:
            type = F("MINUS");
            break;
        default:
            type = F("?");
            break;
    }
    return type;
}