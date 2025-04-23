#include "VirtualDeviceTask.h"
#include "VirtualTemperatureSensor.h"
#include "cmsis_os2.h"

void StartVirtualDeviceTask(void *argument) {
    VirtualTemperatureSensor tempSensor;

    while (1) {
        float temp = tempSensor.getTemperature();
        temp++;
        osDelay(1);
    }
}
