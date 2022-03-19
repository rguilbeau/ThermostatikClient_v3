#include "Container.h"
#include "Pin.h"

Container *Container::instance = nullptr;

Container *Container::get()
{
    if(instance == nullptr) {
        instance = new Container();
    }
    return instance;
}

Container::Container()
{
    _device = new Device();
    _programme = new Programme();

    _clockFactory = new ClockFactory();

    _wifiFactory = new WifiFactory(
        WIFI_SSID, WIFI_PASSWORD
    );

    _receiverFactory = new ReceiverFactory(
        RECEIVER_SSID, RECEIVER_PASSWORD,
        6000,
        new AsyncWebServer(RECEIVER_WEB_PORT)
    );

    _mqttFactory = new MqttFactory(
        new AsyncMqttClient(),
        MQTT_SERVER,  MQTT_PORT, 
        MQTT_LOGIN, MQTT_PASSWORD
    );

    _dhtFactory = new DhtFactory(
        new DHTesp(), PIN_DHT, 2000
    );

    _tftFactory = new TftFactory(
        new TFT_eSPI(),
        PIN_TFT_BRIGHTNESS
    );

    _sleepFactory = new SleepFactory(20000);

    _buttonMore = new Button(PIN_BUTTON_MORE, ButtonType::BUTTON_MORE, 10);
    _buttonMinus = new Button(PIN_BUTTON_MINUS, ButtonType::BUTTON_MINUS, 10);
    _buttonOk = new Button(PIN_BUTTON_OK, ButtonType::BUTTON_OK, 10);

    _topicService = new TopicService(DEVICE_NAME);

    _tftService = new TftService(
        _tftFactory
    );

    _buttonHandler = new ButtonHandler(
        _programme, _device, _sleepFactory
    );

    _messageParserService = new MessageParserService(
        _dhtFactory
    );

    _programmeService = new ProgrammeService(
        _device, _programme, _dhtFactory
    );

    _networkHandler = new NetworkHandler(
        _clockFactory,_wifiFactory, _receiverFactory, _mqttFactory, 
        _dhtFactory, _topicService, _messageParserService, _tftService
    );

    _tftAnimationHandler = new TftAnimationHandler(_tftService);

    _tftDateHandler = new TftDateHandler(_tftService);

    _heatingHandler = new HeatingHandler(
        _programme, _device, 
        _dhtFactory, _mqttFactory, _receiverFactory, _sleepFactory,
        _messageParserService, _programmeService,
        _topicService, _tftService
    );

    _receiverStateHandler = new ReceiverStateHandler(
        _mqttFactory, _messageParserService, _topicService,
        _tftService, _tftAnimationHandler
    );

    _orderHandler = new OrderHandler(
        _device, _programme, 
        _dhtFactory, 
        _programmeService
    );

    _sleepHandler = new SleepHandler(
        _device, _tftFactory
    );

    _dhtSmootherHandler = new DhtSmootherHandler();
}


ClockFactory *Container::clockFactory() { return _clockFactory; }
WifiFactory *Container::wifiFactory() { return _wifiFactory; }
ReceiverFactory *Container::receiverFactory() { return _receiverFactory; }
MqttFactory *Container::mqttFactory() { return _mqttFactory; }
DhtFactory *Container::dhtFactory() { return _dhtFactory; }
TftFactory *Container::tftFactory() { return _tftFactory; }
SleepFactory *Container::sleepFactory() { return _sleepFactory; }

Button *Container::buttonMore() { return _buttonMore; }
Button *Container::buttonMinus() { return _buttonMinus; }
Button *Container::buttonOk() { return _buttonOk; }

NetworkHandler *Container::networkHandler() { return _networkHandler; }
TftAnimationHandler *Container::tftAnimationHandler() { return _tftAnimationHandler; }
HeatingHandler *Container::heatingHandler() { return _heatingHandler; }
ReceiverStateHandler *Container::receiverStateHandler() { return _receiverStateHandler; }
ButtonHandler *Container::buttonHandler() { return _buttonHandler; }
TftDateHandler *Container::tftDateHandler() { return _tftDateHandler; }
OrderHandler *Container::orderHandler() { return _orderHandler; }
SleepHandler *Container::sleepHandler() { return _sleepHandler; }
DhtSmootherHandler *Container::dhtSmootherHandler() { return _dhtSmootherHandler; }

Device *Container::device() { return _device; }
Programme *Container::programme() { return _programme; }

TftService *Container::tftService() { return _tftService; }