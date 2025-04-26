#include "VirtualHumiditySensor.h"
#include "dht11.h"

extern DHT11 dht;
float VirtualHumiditySensor::getHumidity() const {
    // Simulate some constant or random humidity
    float temp, hum;
    if (dht.read(temp, hum)) {
        return hum;
    } else {
        return -1000.0f;  // or some error value
    }
}
