#include "VirtualHumiditySensor.h"
#include "dht11.h"

extern DHT11 dht;
float VirtualHumiditySensor::getHumidity() const {
    dht.init();
    float temp, hum;
    if (dht.read(temp, hum)) {
        return hum;
    } else {
        return -1000.0f;  // or some error value
    }
}
