#include "TftAnimationHandler.h"

TftAnimationHandler::TftAnimationHandler(TftService *tftService)
{
    _tftService = tftService;
    _lastThermometerImage = TftImage::IMAGE_THERMOMETER_EMPTY;
    _thermometerAnimation = false;
}

void TftAnimationHandler::animateThermometer(bool animate)
{
    _lastThermometerImage = TftImage::IMAGE_THERMOMETER_EMPTY;
    _thermometerAnimation = animate;
}

void TftAnimationHandler::clockHandle()
{
    if(_thermometerAnimation) {
        switch (_lastThermometerImage) {
            case TftImage::IMAGE_THERMOMETER_EMPTY :
                _lastThermometerImage = TftImage::IMAGE_THERMOMETER_QUARTER;
                break;
            case TftImage::IMAGE_THERMOMETER_QUARTER :
                _lastThermometerImage = TftImage::IMAGE_THERMOMETER_HALF;
                break;
            case TftImage::IMAGE_THERMOMETER_HALF :
                _lastThermometerImage = TftImage::IMAGE_THERMOMETER_THREE_QUARTER;
                break;
            case TftImage::IMAGE_THERMOMETER_THREE_QUARTER :
                _lastThermometerImage = TftImage::IMAGE_THERMOMETER_FULL;
                break;
            case TftImage::IMAGE_THERMOMETER_FULL :
                _lastThermometerImage = TftImage::IMAGE_THERMOMETER_EMPTY;
                break;
            default:
                _lastThermometerImage = TftImage::IMAGE_THERMOMETER_EMPTY;
                break;
        }

        ThermometerRender render;
        render.image = _lastThermometerImage;
        _tftService->setThermometerRender(render);
    }
}