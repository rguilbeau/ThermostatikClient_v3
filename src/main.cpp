#include <Arduino.h>
#include <SPI.h> // required for TFT
#include "FS.h"

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

    if(!SPIFFS.begin()) {
        #ifdef DEBUG
            Serial.println("Unable to mount filesysteme !");
        #endif
    }

    WiFi.mode(WIFI_AP_STA);

    container = Container::get();

    container->tftService()->message("Connexion au wifi...");

    container->programmeFactory()->setOrderHandler(container->heatingHandler());
    container->programmeFactory()->setUntilDateHandler(container->heatingHandler());
    container->clockFactory()->setHandlerSize(2);
    container->clockFactory()->setHandler(0, 500, container->tftAnimationHandler());
    container->clockFactory()->setHandler(0, 1000, container->tftDateHandler());
    container->clockFactory()->setNtpHandler(container->networkHandler());

    container->wifiFactory()->setHandler(container->networkHandler());
    container->receiverFactory()->setStateHandler(container->receiverStateHandler());
    container->mqttFactory()->setConnectionHandler(container->networkHandler());
    container->mqttFactory()->setMessageHandler(container->heatingHandler());
    container->dhtFactory()->setHandler(container->heatingHandler());

    container->wifiFactory()->setHandler(container->networkHandler());
    container->receiverFactory()->setConnectionHandler(container->networkHandler());

    container->buttonMore()->setHandler(container->buttonHandler());
    container->buttonMinus()->setHandler(container->buttonHandler());
    container->buttonOk()->setHandler(container->buttonHandler());
    container->buttonHandler()->setHeatingHandler(container->heatingHandler());

    container->tftService()->displayDefault();

    container->receiverFactory()->createAccessPoint();
    container->wifiFactory()->connect();
}

void loop()
{
    container->buttonMore()->loop();
    container->buttonMinus()->loop();
    container->buttonOk()->loop();
    container->dhtFactory()->loop();
    container->programmeFactory()->loop();
    container->clockFactory()->loop();
    container->receiverFactory()->loop();

    #ifdef DISPLAY_FREE_MEMORY
        freeMemoryService->loop();
    #endif
}