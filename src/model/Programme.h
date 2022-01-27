#ifndef T_PROGRAMME_H
#define T_PROGRAMME_H

#include <Arduino.h>

#include "utils/Date.h"

#include "Order.h"
#include "OrderTime.h"

const int PROGRAMME_MAX_TIMES_ORDERS = 12 * 7;
const int PROGRAMME_MAX_ORDERS = 10;

class Programme {

public:
    Programme();

    Order *findOrderAt(Date date);
    Order *findAnticipatingOrderAt(Order *currentOrder, Date date);
    
    Order *getLastOrder();
    Order *getAnticipatingOrder();

    void setLastOrder(Order *order);
    void setAnticipatingOrder(Order *order);

    String getLabel();
    void setLabel(String label);

    Order *getOrder(int index);
    OrderTime *getOrderTime(int index);

private:

    String _label;
    Order *_lastOrder;
    Order *_anticipatingOrder;
    OrderTime *_ordersTimes[PROGRAMME_MAX_TIMES_ORDERS]{};
    Order *_orders[PROGRAMME_MAX_ORDERS]{};
};

#endif