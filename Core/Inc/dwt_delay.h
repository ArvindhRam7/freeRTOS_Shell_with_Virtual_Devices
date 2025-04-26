#pragma once

#include <stdint.h>
#include "stm32f1xx.h"

#ifdef __cplusplus
extern "C" {
#endif

void DWT_Delay_Init(void);
void DWT_Delay_us(uint32_t us);
// ... other functions

#ifdef __cplusplus
}
#endif
