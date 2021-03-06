#ifndef T_BUTTON_HANDLER_H
#define T_BUTTON_HANDLER_H

#include <Arduino.h>
#include "Debug.h"

#include "service/heating/Heating.h"

#include "model/Device.h"
#include "model/Programme.h"

#include "handler/interface/ModeHandlerInterface.h"

#include "factory/button/ButtonHandlerInterface.h"

#include "factory/sleep/SleepFactory.h"

class ButtonHandler : public ButtonHandlerInterface {

public:
    ButtonHandler(
        Programme *programme,
        Device *device,
        SleepFactory *sleepFactory
    );
    
    void pushed(ButtonType buttonType, String name) override;
    void setHeatingHandler(ModeHandlerInterface *modeHandler);

private:
    ModeHandlerInterface *_modeHandler;

    Programme *_programme;
    Device *_device;
    SleepFactory *_sleepFactory;
};

#endif