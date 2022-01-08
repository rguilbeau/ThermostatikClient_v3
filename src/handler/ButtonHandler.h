#ifndef T_BUTTON_HANDLER_H
#define T_BUTTON_HANDLER_H

#include <Arduino.h>
#include "Debug.h"

#include "factory/button/ButtonHandlerInterface.h"

class ButtonHandler : public ButtonHandlerInterface {

public:
    ButtonHandler();
    
    void pushed(ButtonType buttonType, String name) override;

};

#endif