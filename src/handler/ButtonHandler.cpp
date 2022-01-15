#include "ButtonHandler.h"

ButtonHandler::ButtonHandler(
    Programme *programme,
    Device *device
) {
    _programme = programme;
    _device = device;
}

void ButtonHandler::setHeatingHandler(ModeHandlerInterface *modeHandler)
{
    _modeHandler = modeHandler;
}

void ButtonHandler::pushed(ButtonType buttontype, String name)
{
    #ifdef DEBUG
        Serial.println("Button " + name + " pushed");
    #endif

    bool hasMuted = false;
    
    Heating *heating = Heating::getMode(_device, _programme);

    switch (buttontype) {
        case BUTTON_OK:
            hasMuted = heating->nextMode();
            break;
        case BUTTON_MINUS:
            hasMuted = heating->forceTemperature(-0.5); 
            break;
        case BUTTON_MORE:
            hasMuted = heating->forceTemperature(+0.5);
            break;
        default:
            break;
    }

    delete heating;

    if(hasMuted && _modeHandler != nullptr) {
        _modeHandler->modeUpdated();
    }
}