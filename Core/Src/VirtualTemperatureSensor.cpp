#include "VirtualTemperatureSensor.h"
#include <cstdlib>
#include "dht11.h"

DHT11 dht(GPIOA, GPIO_PIN_1);

VirtualTemperatureSensor::VirtualTemperatureSensor() {
    // Initialization if needed
}

float VirtualTemperatureSensor::getTemperature() {
    float temp, hum;
    if (dht.read(temp, hum)) {
        return temp;
    } else {
        return -1000.0f;  // or some error value
    }
}
