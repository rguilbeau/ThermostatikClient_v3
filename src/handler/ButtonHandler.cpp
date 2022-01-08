#include "ButtonHandler.h"

ButtonHandler::ButtonHandler()
{

}

void ButtonHandler::pushed(ButtonType buttontype, String name)
{
    #ifdef DEBUG
        Serial.println("Button " + name + " pushed");
    #endif
}