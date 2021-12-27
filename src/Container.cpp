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

    _mqttFactory = new MqttFactory(
        new AsyncMqttClient(),
        MQTT_SERVER,  MQTT_PORT, 
        MQTT_LOGIN, MQTT_PASSWORD
    );

    _dhtFactory = new DhtFactory(
        10, 60000
    );

    _relayFactory = new RelayFactory();

    _topicService = new TopicService(DEVICE_NAME);

    _messageParserService = new MessageParserService();

    _networkHandler = new NetworkHandler(
        _clockFactory,_wifiFactory, _mqttFactory, 
        _dhtFactory, _relayFactory, _topicService, _messageParserService
    );

    _thermometerAnimationHandler = new ThermometerAnimationHandler();

    _relayHandler = new RelayHandler(
        _mqttFactory,
        _messageParserService, _topicService
    );

    _heatingHandler = new HeatingHandler(
        _programme, _device, 
        _dhtFactory, _relayFactory, _mqttFactory, 
        _messageParserService, 
        _topicService
    );
}

ProgrammeFactory *Container::programmeFactory() { return _programmeFactory; }
ClockFactory *Container::clockFactory() { return _clockFactory; }
WifiFactory *Container::wifiFactory() { return _wifiFactory; }
MqttFactory *Container::mqttFactory() { return _mqttFactory; }
DhtFactory *Container::dhtFactory() { return _dhtFactory; }
RelayFactory *Container::relayFactory() { return _relayFactory; }

NetworkHandler *Container::networkHandler() { return _networkHandler; }
RelayHandler *Container::relayHandler() { return _relayHandler; }
ThermometerAnimationHandler *Container::thermometerAnimationHandler() { return _thermometerAnimationHandler; }
HeatingHandler *Container::heatingHandler() { return _heatingHandler; }

Device *Container::device() { return _device; }
Programme *Container::programme() { return _programme; }