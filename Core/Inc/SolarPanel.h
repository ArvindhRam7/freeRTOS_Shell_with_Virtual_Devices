#pragma once

#include "main.h"
#include <cmath>

class SolarPanel {
public:
	SolarPanel(int currentHour);


    float calculateSolarIntensity();
    float calculateSolarCurrent();
    float calculateSolarPower();

private:
    static const float VOLTAGE;
    static const float MAX_CURRENT;
    int hour;
};

