#include "ShellTask.h"
#include "VirtualTemperatureSensor.h"
#include "VirtualHumiditySensor.h"
#include "VirtualVoltageSensor.h"
#include "stm32f1xx_ll_usart.h"
#include "cmsis_os2.h"
#include <cstring>
#include <cstdio>

extern "C" {
#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "core_cm3.h"
}
#include "UartRxStream.h"

#define BUFFER_SIZE 100

extern UART_HandleTypeDef huart2;
extern RTC_HandleTypeDef hrtc;

void GetCurrentTime(char *response, size_t max_len) {
	RTC_TimeTypeDef sTime;
	RTC_DateTypeDef sDate;

	// Get current time and date
	if (HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK) {
		snprintf(response, max_len, "Error getting time\n");
		return;
	}
	if (HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK) {
		snprintf(response, max_len, "Error getting date\n");
		return;
	}

	// Format the time and date as string
	snprintf(response, max_len, "Time: %02d:%02d:%02d Date: %02d-%02d-%04d\n",
			sTime.Hours, sTime.Minutes, sTime.Seconds, sDate.Date, sDate.Month,
			2000 + sDate.Year);
}

void StartShellTask(void *argument) {
	VirtualTemperatureSensor tempSensor;
	VirtualHumiditySensor humiditySensor;
	VirtualVoltageSensor voltageSensor;

	char rxChar;
	char command[100];
	char response[100];
	unsigned int cmdIndex = 0;

	while (1) {
		// Read one byte at a time
		if (xStreamBufferReceive(uartRxStreamBuffer, &rxChar, 1, portMAX_DELAY) == 1) {
			if (rxChar == '\r' || rxChar == '\n') {
				command[cmdIndex] = '\0'; // Null-terminate
				cmdIndex = 0;

				// Trim any trailing newline or carriage return
				command[strcspn(command, "\r\n")] = 0;

				if (strcmp(command, "GET_TEMPERATURE") == 0) {
					float temp = tempSensor.getTemperature();
					snprintf(response, sizeof(response), "Temperature: %.2foC\n", temp);
				} else if (strcmp(command, "GET_HUMIDITY") == 0) {
					float hum = humiditySensor.getHumidity();
					snprintf(response, sizeof(response), "Humidity: %.2f%%\n", hum);
				} else if (strcmp(command, "GET_VOLTAGE") == 0) {
					float volt = voltageSensor.getVoltage();
					snprintf(response, sizeof(response), "Voltage: %.2f V\n", volt);
				} else if (strcmp(command, "GET_TIME") == 0) {
					RTC_TimeTypeDef time;
					RTC_DateTypeDef date;
					HAL_RTC_GetTime(&hrtc, &time, RTC_FORMAT_BIN);
					HAL_RTC_GetDate(&hrtc, &date, RTC_FORMAT_BIN);
					snprintf(response, sizeof(response),
						"Time: %02d:%02d:%02d, Date: %02d/%02d/%04d\n",
						time.Hours, time.Minutes, time.Seconds,
						date.Date, date.Month, 2000 + date.Year);
				} else if (strncmp(command, "SET_TIME", 8) == 0) {
					int hh, mm, ss, dd, mo, yyyy;
					if (sscanf(command + 9, "%d %d %d %d %d %d", &hh, &mm, &ss, &dd, &mo, &yyyy) == 6) {
						RTC_TimeTypeDef sTime = {0};
						RTC_DateTypeDef sDate = {0};

						sTime.Hours = hh;
						sTime.Minutes = mm;
						sTime.Seconds = ss;
						sDate.Date = dd;
						sDate.Month = mo;
						sDate.Year = yyyy - 2000;
						sDate.WeekDay = RTC_WEEKDAY_MONDAY; // Not used by HAL

						if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) == HAL_OK &&
							HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) == HAL_OK) {
							snprintf(response, sizeof(response), "Time set successfully\n");
						} else {
							snprintf(response, sizeof(response), "Failed to set time\n");
						}
					} else {
						snprintf(response, sizeof(response), "Usage: SET_TIME hh mm ss dd mm yyyy\n");
					}
				} else if (strlen(command) > 0) {
					snprintf(response, sizeof(response), "Unknown command\n");
				} else {
					response[0] = '\0'; // empty command, don't respond
				}

				if (strlen(response) > 0) {
					HAL_UART_Transmit(&huart2, (uint8_t*) response, strlen(response), HAL_MAX_DELAY);
				}
			} else if (cmdIndex < sizeof(command) - 1) {
				command[cmdIndex++] = rxChar;
			}
		}
	}
}

