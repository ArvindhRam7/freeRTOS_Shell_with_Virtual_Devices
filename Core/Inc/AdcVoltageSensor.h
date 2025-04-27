#pragma once

#include "stm32f1xx_hal.h"

class AdcVoltageSensor {
public:
    AdcVoltageSensor(ADC_HandleTypeDef* hadc);
    float readVoltage();

private:
    ADC_HandleTypeDef* m_hadc;
};
