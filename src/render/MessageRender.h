#ifndef T_MESSAGE_RENDER_H
#define T_MESSAGE_RENDER_H

#include <Arduino.h>
#include "utils/Date.h"

struct MessageRender {
    String message = "Initialisation";
    Date date;
};


#endif