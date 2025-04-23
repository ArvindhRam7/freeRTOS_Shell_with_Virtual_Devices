#include "VirtualTemperatureSensor.h"
#include <cstdlib>

VirtualTemperatureSensor::VirtualTemperatureSensor() {
    // Initialization if needed
}

float VirtualTemperatureSensor::getTemperature() {
    return 25.0f + (rand() % 10); // Simulate 25–35°C
}
