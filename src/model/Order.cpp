#include "Order.h"

Order::Order()
{
    _id = 0;
    _label = "";
    _temperature = 0;
    _used = false;
}

void Order::update(int id, String label, float temperature)
{
    _used = true;
    _id = id;
    _label = label;
    _temperature = temperature;
}

void Order::unused()
{
    _used = false;
}

int Order::getId()
{
    return _id;
}

String Order::getLabel()
{
    return _label;
}

float Order::getTemperature()
{
    return _temperature;
}

bool Order::isUsed()
{
    return _used;
}