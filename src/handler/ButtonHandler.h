#ifndef T_BUTTON_HANDLER_H
#define T_BUTTON_HANDLER_H

#include <Arduino.h>
#include "Debug.h"

#include "service/heating/Heating.h"

#include "model/Device.h"
#include "model/Programme.h"

#include "factory/programme/ModeHandlerInterface.h"

#include "factory/button/ButtonHandlerInterface.h"

class ButtonHandler : public ButtonHandlerInterface {

public:
    ButtonHandler(
        Programme *programme,
        Device *device
    );
    
    void pushed(ButtonType buttonType, String name) override;
    void setHeatingHandler(ModeHandlerInterface *modeHandler);

private:
    ModeHandlerInterface *_modeHandler;

    Programme *_programme;
    Device *_device;
};

#endif