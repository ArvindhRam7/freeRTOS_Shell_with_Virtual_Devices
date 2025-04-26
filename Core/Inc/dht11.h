#pragma once

#include "main.h"

class DHT11 {
public:
    DHT11(GPIO_TypeDef* port, uint16_t pin);
    void init();
    bool read(float& temperature, float& humidity);

private:
    GPIO_TypeDef* _port;
    uint16_t _pin;

    void setPinOutput();
    void setPinInput();
    uint8_t waitForLevel(GPIO_PinState level, uint32_t timeout_us);
};
