# FreeRTOS Shell with Virtual Devices

This project is an STM32F103RB Nucleo board application that demonstrates:
- A basic Shell (UART-based) running on FreeRTOS
- Virtual devices like Temperature Sensor, Humidity Sensor (DHT11 Sensor), Solar Panel
- Real ADC Voltage reading via PA0
- RTC time management

## Features

- **FreeRTOS Shell** for command-line interface
- **Virtual Sensors**: Temperature, Humidity (DHT11), Solar Panel Power
- **Real ADC Voltage** reading using hardware ADC
- **RTC** integration to get and set system time

## Commands Available

| Command | Description |
|:---|:---|
| `GET_TEMPERATURE` | Reads virtual temperature |
| `GET_HUMIDITY` | Reads virtual humidity |
| `GET_SOLAR_INTENSITY` | Reads solar panel intensity |
| `GET_SOLAR_CURRENT` | Reads solar panel current |
| `GET_SOLAR_POWER` | Reads solar panel power |
| `GET_VOLTAGE` | Reads real voltage from PA0 using ADC |
| `GET_TIME` | Shows current RTC time and date |
| `SET_TIME hh mm ss dd mm yyyy` | Sets the RTC time and date |

## Hardware Connections

- **UART**: UART2 (USB via Nucleo ST-Link)
- **ADC Input**: PA0 connected to potentiometer or voltage divider
- **Power**: 3.3V supply from Nucleo board

## How to Build

1. Open project in STM32CubeIDE
2. Build the project
3. Flash to Nucleo board
4. Connect Serial Monitor (115200 baud)
5. Start sending shell commands!

