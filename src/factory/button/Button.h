#ifndef T_BUTTON_H
#define T_BUTTON_H

#include "ButtonType.h"
#include "factory/button/ButtonHandlerInterface.h"

#include <Arduino.h>

class Button {

public:
    Button(uint8_t pin, ButtonType buttonType, int debounce);

    void setHandler(ButtonHandlerInterface *hander);

    void loop();
    
    ButtonType getType();
    String getTypeStr();

private:
    ButtonHandlerInterface *_handler;
    ButtonType _buttonType;
    uint8_t _pin;
    bool _pushed;
    int _debounce;
    unsigned long _lastCheck;
};

#endif