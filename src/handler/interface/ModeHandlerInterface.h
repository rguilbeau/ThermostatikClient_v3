#ifndef T_MODE_HANDLER_INTERFACE_H
#define T_MODE_HANDLER_INTERFACE_H

#include "service/heating/Heating.h"

class ModeHandlerInterface {

public:

    virtual void modeUpdated(Heating *heating) = 0;

};

#endif