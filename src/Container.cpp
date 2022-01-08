#include "Container.h"

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

    _programmeFactory = new ProgrammeFactory(
        _programme, _device 
    );

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
        10, 60000
    );

    _buttonMore = new Button(D5, ButtonType::BUTTON_MORE, 50);
    _buttonMinus = new Button(D6, ButtonType::BUTTON_MINUS, 50);
    _buttonOk = new Button(D7, ButtonType::BUTTON_OK, 50);

    _topicService = new TopicService(DEVICE_NAME);

    _buttonHandler = new ButtonHandler();

    _messageParserService = new MessageParserService(
        _dhtFactory
    );

    _networkHandler = new NetworkHandler(
        _clockFactory,_wifiFactory, _receiverFactory, _mqttFactory, 
        _dhtFactory, _topicService, _messageParserService
    );

    _thermometerAnimationHandler = new ThermometerAnimationHandler();

    _heatingHandler = new HeatingHandler(
        _programme, _device, 
        _dhtFactory, _mqttFactory, _receiverFactory, 
        _messageParserService, 
        _topicService
    );

    _receiverStateHandler = new ReceiverStateHandler(
        _mqttFactory, _messageParserService, _topicService
    );
}

ProgrammeFactory *Container::programmeFactory() { return _programmeFactory; }
ClockFactory *Container::clockFactory() { return _clockFactory; }
WifiFactory *Container::wifiFactory() { return _wifiFactory; }
ReceiverFactory *Container::receiverFactory() { return _receiverFactory; }
MqttFactory *Container::mqttFactory() { return _mqttFactory; }
DhtFactory *Container::dhtFactory() { return _dhtFactory; }
Button *Container::buttonMore() { return _buttonMore; }
Button *Container::buttonMinus() { return _buttonMinus; }
Button *Container::buttonOk() { return _buttonOk; }

NetworkHandler *Container::networkHandler() { return _networkHandler; }
ThermometerAnimationHandler *Container::thermometerAnimationHandler() { return _thermometerAnimationHandler; }
HeatingHandler *Container::heatingHandler() { return _heatingHandler; }
ReceiverStateHandler *Container::receiverStateHandler() { return _receiverStateHandler; }
ButtonHandler *Container::buttonHandler() { return _buttonHandler; }

Device *Container::device() { return _device; }
Programme *Container::programme() { return _programme; }