#include "TftDateHandler.h"

TftDateHandler::TftDateHandler(TftService *tftService)
{
    _tftService = tftService;
    _lastTimeMin = -1;
}

void TftDateHandler::clockHandle()
{
    if(Date::timeInitialized) {
        Date now;
        if(now.getTimeMin() != _lastTimeMin) {
            _lastTimeMin = now.getTimeMin();

            DateRender render;
            render.date = now.toLongFormat();
            _tftService->setMessageRender(render);
        }
    }
}