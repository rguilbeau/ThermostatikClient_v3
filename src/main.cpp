#include <Arduino.h>
#include <AsyncMqttClient.h>

#include "Container.h"
#include "Debug.h"

#include "service/FreeMemoryService.h"

#ifdef DISPLAY_FREE_MEMORY
    FreeMemoryService *freeMemoryService = new FreeMemoryService(1000);
#endif

Container *container = nullptr;

void startSerial() {
    Serial.begin(9600);
    delay(2000);
    Serial.println("Serial started");
}

void setup()
{
    #ifdef DEBUG
        startSerial();
    #elif DISPLAY_FREE_MEMORY
        startSerial();
    #endif

    container = Container::get();

    container->programmeFactory()->setOrderHandler(container->heatingHandler());
    container->programmeFactory()->setUntilDateHandler(container->heatingHandler());
    container->clockFactory()->setHandlerSize(1);
    container->clockFactory()->setHandler(0, 1000, container->thermometerAnimationHandler());
    container->clockFactory()->setNtpHandler(container->networkHandler());

    container->wifiFactory()->setHandler(container->networkHandler());
    container->mqttFactory()->setConnectionHandler(container->networkHandler());
    container->mqttFactory()->setMessageHandler(container->heatingHandler());
    container->dhtFactory()->setHandler(container->heatingHandler());
    container->relayFactory()->setHandler(container->relayHandler());

    container->wifiFactory()->connect();
}

void loop()
{
    container->dhtFactory()->loop();
    container->programmeFactory()->loop();
    container->clockFactory()->loop();

    #ifdef DISPLAY_FREE_MEMORY
        freeMemoryService->loop();
    #endif
}