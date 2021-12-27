#ifndef T_ORDER_H
#define T_ORDER_H

#include <Arduino.h>

class Order {

public:
    Order();
    
    void update(int id, String lable, float temperature);
    void unused();

    int getId();
    String getLabel();
    float getTemperature();
    bool isUsed();

private:
    bool _used;
    int _id;
    String _label;
    float _temperature;
};

#endif