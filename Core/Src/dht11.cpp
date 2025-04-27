#include "dht11.h"
#include "dwt_delay.h"
#include <cstring>
#include <cstdio>
#include "cmsis_os.h"
extern UART_HandleTypeDef huart2;

#define CPU_CYCLES_PER_US (SystemCoreClock / 1000000U)

DHT11::DHT11(GPIO_TypeDef* port, uint16_t pin)
    : _port(port), _pin(pin) {}

void DHT11::init() {
    DWT_Delay_Init();
}

void DHT11::setPinOutput() {
    GPIO_InitTypeDef GPIO_InitStruct = {};
    GPIO_InitStruct.Pin = _pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(_port, &GPIO_InitStruct);
}

void DHT11::setPinInput() {
    GPIO_InitTypeDef GPIO_InitStruct = {};
    GPIO_InitStruct.Pin = _pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(_port, &GPIO_InitStruct);
}

uint8_t DHT11::waitForLevel(GPIO_PinState level, uint32_t timeout_us) {
    uint32_t timeout_cycles = timeout_us * CPU_CYCLES_PER_US;
    uint32_t start = DWT->CYCCNT;
    while (HAL_GPIO_ReadPin(_port, _pin) != level) {
        if ((DWT->CYCCNT - start) > timeout_cycles) return 1;
    }
    return 0;
}

bool DHT11::read(float& temperature, float& humidity) {
    uint8_t bits[5] = {0};

    setPinOutput();
    HAL_GPIO_WritePin(_port, _pin, GPIO_PIN_RESET);
    DWT_Delay_us(18000);
    HAL_GPIO_WritePin(_port, _pin, GPIO_PIN_SET);
    DWT_Delay_us(20);
    setPinInput();

    if (waitForLevel(GPIO_PIN_RESET, 100)) return false;
    if (waitForLevel(GPIO_PIN_SET, 100)) return false;
    if (waitForLevel(GPIO_PIN_RESET, 100)) return false;

    for (int i = 0; i < 40; i++) {
        if (waitForLevel(GPIO_PIN_SET, 100)) return false;

        DWT_Delay_us(35);
        if (HAL_GPIO_ReadPin(_port, _pin) == GPIO_PIN_SET) {
            bits[i / 8] |= (1 << (7 - (i % 8)));
        }

        if (waitForLevel(GPIO_PIN_RESET, 100)) return false;
    }

    if ((uint8_t)(bits[0] + bits[1] + bits[2] + bits[3]) != bits[4]) return false;

    humidity = static_cast<float>(bits[0]);
    temperature = static_cast<float>(bits[2]);

    return true;
}

//void DHT11_Task(void *argument) {
//    DHT11 sensor(GPIOA, GPIO_PIN_1);
//    sensor.init();
//
//    float temp, hum;
//    char buffer[64];
//
//    for (;;) {
//        if (sensor.read(temp, hum)) {
//            snprintf(buffer, sizeof(buffer), "Temp: %.1f °C, Humidity: %.1f %%\r\n", temp, hum);
//        } else {
//            snprintf(buffer, sizeof(buffer), "DHT11 read failed\r\n");
//        }
//        HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), HAL_MAX_DELAY);
//
//        osDelay(2000);
//    }
//}
