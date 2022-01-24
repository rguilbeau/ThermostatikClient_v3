#include "TftDateHandler.h"

TftDateHandler::TftDateHandler(TftService *tftService)
{
    _tftService = tftService;
    _lastTimeMin = -1;
}

void TftDateHandler::enable()
{
    _dateUpdateEnabled = true;
    _lastTimeMin = -1;
}

void TftDateHandler::disable()
{
    _dateUpdateEnabled = false;
}

void TftDateHandler::clockHandle()
{
    if(Date::timeInitialized && _dateUpdateEnabled) {
        Date now;
        if(now.getTimeMin() != _lastTimeMin) {
            _lastTimeMin = now.getTimeMin();

            MessageRender render;
            render.date = now;
            _tftService->setMessageRender(render);
        }
    }
}