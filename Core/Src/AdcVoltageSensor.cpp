#include "AdcVoltageSensor.h"

AdcVoltageSensor::AdcVoltageSensor(ADC_HandleTypeDef* hadc) : m_hadc(hadc) {}

float AdcVoltageSensor::readVoltage() {
    HAL_ADC_Start(m_hadc);
    if (HAL_ADC_PollForConversion(m_hadc, 10) == HAL_OK) {
        uint32_t adcValue = HAL_ADC_GetValue(m_hadc);
        float voltage = (adcValue / 4095.0f) * 3.3f;
        HAL_ADC_Stop(m_hadc);
        return voltage;
    }
    HAL_ADC_Stop(m_hadc);
    return 0.0f;
}
