#include "HeatingProgramme.h"

HeatingProgramme::HeatingProgramme(Device *device, Programme *programme) : Heating(device, programme)
{

}

HeatingProgramme::~HeatingProgramme()
{

}

bool HeatingProgramme::regulationStatus(float currentTemperature)
{
    Order *order = _programme->getLastOrder();
    
    #ifdef DEBUG
        Serial.print("Regulation : Programme, Order:");
        Serial.print(order == nullptr ? "null" : order->getLabel());

        if(order == nullptr) {
            Serial.println();
        }
    #endif

    if(order != nullptr) {
        return _regulateByTemperature(order->getTemperature(), currentTemperature);
    } else {
        return false;
    }
}