#include <Arduino.h>
#include <SPI.h> // required for TFT
#include "FS.h"

#include "Container.h"
#include "Debug.h"

#include "service/FreeMemoryService.h"

#ifdef DEBUG
    FreeMemoryService *freeMemoryService = new FreeMemoryService(1000);
#endif

Container *container = nullptr;

void setup()
{
    #ifdef DEBUG
        Serial.begin(9600);
        delay(1000);

        if(!SPIFFS.begin()) {
            Serial.println(F("Unable to mount filesysteme !"));
        }
    #endif

    container = Container::get();
    container->tftFactory()->setBrightness(0);   

    WiFi.mode(WIFI_AP_STA);

    container = Container::get();
    container->tftFactory()->clear();
    container->tftService()->displayDefault();
    container->tftFactory()->setBrightness(container->device()->getBrightnessMax());
    
    container->sleepFactory()->setHandler(container->sleepHandler());
    container->sleepFactory()->invokeHandler();

    container->wifiFactory()->setHandler(container->networkHandler());
    container->receiverFactory()->setConnectionHandler(container->networkHandler());
    container->mqttFactory()->setConnectionHandler(container->networkHandler());

    container->receiverFactory()->setStateHandler(container->receiverStateHandler());
    container->mqttFactory()->setMessageHandler(container->heatingHandler());
    container->dhtFactory()->setSmoother(container->dhtSmootherHandler());
    container->dhtFactory()->setHandler(container->heatingHandler());

    container->buttonMore()->setHandler(container->buttonHandler());
    container->buttonMinus()->setHandler(container->buttonHandler());
    container->buttonOk()->setHandler(container->buttonHandler());
    container->buttonHandler()->setHeatingHandler(container->heatingHandler());

    container->orderHandler()->setOrderUpdatedHandler(container->heatingHandler());
    container->orderHandler()->setUntilDateHandler(container->heatingHandler());

    container->clockFactory()->setHandlerSize(3);
    container->clockFactory()->setHandler(0, 500, container->tftAnimationHandler());
    container->clockFactory()->setHandler(1, 1000, container->tftDateHandler());
    container->clockFactory()->setHandler(2, 1000, container->orderHandler());
    container->clockFactory()->setNtpHandler(container->networkHandler());

    container->receiverFactory()->createAccessPoint();
    container->wifiFactory()->connect();
}

void loop()
{ 
    container->buttonMore()->loop();
    container->buttonMinus()->loop();
    container->buttonOk()->loop();
    container->dhtFactory()->loop();
    container->clockFactory()->loop();
    container->receiverFactory()->loop();
    container->sleepFactory()->loop();
    container->tftService()->loop();

    #ifdef DEBUG
        freeMemoryService->loop();
    #endif
}