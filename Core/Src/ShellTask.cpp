#include <SolarPanel.h>
#include "ShellTask.h"
#include "VirtualTemperatureSensor.h"
#include "VirtualHumiditySensor.h"
#include "stm32f1xx_ll_usart.h"
#include "cmsis_os2.h"
#include <cstring>
#include <cstdio>
#include "AdcVoltageSensor.h"
extern "C" {
#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "core_cm3.h"
}
#include "UartRxStream.h"

#define BUFFER_SIZE 100

extern UART_HandleTypeDef huart2;
extern RTC_HandleTypeDef hrtc;
extern ADC_HandleTypeDef hadc1;

void GetCurrentTime(char *response, size_t max_len) {
	RTC_TimeTypeDef sTime;
	RTC_DateTypeDef sDate;

	// Get current time and date
	if (HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK) {
		snprintf(response, max_len, "Error getting time\r\n");
		return;
	}
	if (HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK) {
		snprintf(response, max_len, "Error getting date\r\n");
		return;
	}

	// Format the time and date as string
	snprintf(response, max_len, "Time: %02d:%02d:%02d Date: %02d-%02d-%04d\r\n",
			sTime.Hours, sTime.Minutes, sTime.Seconds, sDate.Date, sDate.Month,
			2000 + sDate.Year);
}

void StartShellTask(void *argument) {
	VirtualTemperatureSensor tempSensor;
	VirtualHumiditySensor humiditySensor;
	SolarPanel solarPanel(13);
	AdcVoltageSensor adcVoltageSensor(&hadc1);
	char rxChar;
	char command[100];
	char response[100];
	unsigned int cmdIndex = 0;

	while (1) {
		// Read one byte at a time
		if (xStreamBufferReceive(uartRxStreamBuffer, &rxChar, 1, portMAX_DELAY)
				== 1) {
			if (rxChar == '\r' || rxChar == '\n') {
				command[cmdIndex] = '\0'; // Null-terminate
				cmdIndex = 0;

				// Trim any trailing newline or carriage return
				command[strcspn(command, "\r\n")] = 0;

				if (strcmp(command, "GET_TEMPERATURE") == 0) {
					float temp = tempSensor.getTemperature();
					snprintf(response, sizeof(response),
							"Temperature: %.2foC\r\n", temp);
				} else if (strcmp(command, "GET_HUMIDITY") == 0) {
					float hum = humiditySensor.getHumidity();
					snprintf(response, sizeof(response), "Humidity: %.2f%%\r\n",
							hum);
				} else if (strcmp(command, "GET_SOLAR_INTENSITY") == 0) {
					float intensity = solarPanel.calculateSolarIntensity();
					snprintf(response, sizeof(response),
							"Solar Panel Intensity: %.2f W/m2\r\n", intensity);
				} else if (strcmp(command, "GET_SOLAR_CURRENT") == 0) {
					float current = solarPanel.calculateSolarCurrent();
					snprintf(response, sizeof(response),
							"Solar Panel Current: %.2f A\r\n", current);
				} else if (strcmp(command, "GET_SOLAR_POWER") == 0) {
					float power = solarPanel.calculateSolarPower();
					snprintf(response, sizeof(response),
							"Solar Panel Power: %.2f W\r\n", power);
				} else if (strcmp(command, "GET_TIME") == 0) {
					RTC_TimeTypeDef time;
					RTC_DateTypeDef date;
					HAL_RTC_GetTime(&hrtc, &time, RTC_FORMAT_BIN);
					HAL_RTC_GetDate(&hrtc, &date, RTC_FORMAT_BIN);
					snprintf(response, sizeof(response),
							"Time: %02d:%02d:%02d, Date: %02d/%02d/%04d\r\n",
							time.Hours, time.Minutes, time.Seconds, date.Date,
							date.Month, 2000 + date.Year);
				} else if (strncmp(command, "SET_TIME", 8) == 0) {
					int hh, mm, ss, dd, mo, yyyy;
					if (sscanf(command + 9, "%d %d %d %d %d %d", &hh, &mm, &ss,
							&dd, &mo, &yyyy) == 6) {
						RTC_TimeTypeDef sTime = { 0 };
						RTC_DateTypeDef sDate = { 0 };

						sTime.Hours = hh;
						sTime.Minutes = mm;
						sTime.Seconds = ss;
						sDate.Date = dd;
						sDate.Month = mo;
						sDate.Year = yyyy - 2000;
						sDate.WeekDay = RTC_WEEKDAY_MONDAY; // Not used by HAL

						if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN)
								== HAL_OK && HAL_RTC_SetDate(&hrtc, &sDate,
						RTC_FORMAT_BIN) == HAL_OK) {
							snprintf(response, sizeof(response),
									"Time set successfully\r\n");
						} else {
							snprintf(response, sizeof(response),
									"Failed to set time\r\n");
						}
					} else {
						snprintf(response, sizeof(response),
								"Usage: SET_TIME hh mm ss dd mm yyyy\r\n");
					}
				} else if (strcmp(command, "GET_VOLTAGE") == 0) {
					float voltage = adcVoltageSensor.readVoltage();
					snprintf(response, sizeof(response),
							"ADC Voltage: %.2f V\r\n", voltage);
				} else if (strlen(command) > 0) {
					snprintf(response, sizeof(response), "Unknown command\r\n");
				} else {
					response[0] = '\0'; // empty command, don't respond
				}

				if (strlen(response) > 0) {
					HAL_UART_Transmit(&huart2, (uint8_t*) response,
							strlen(response), HAL_MAX_DELAY);
				}
			} else if (cmdIndex < sizeof(command) - 1) {
				command[cmdIndex++] = rxChar;
			}
		}
	}
}
