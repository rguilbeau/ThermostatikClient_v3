#ifndef T_BUTTON_HANDLER_INTERFACE_H
#define T_BUTTON_HANDLER_INTERFACE_H

#include <Arduino.h>
#include "ButtonType.h"

class ButtonHandlerInterface {

public:

    virtual void pushed(ButtonType buttonType, String name) = 0;

};

#endif