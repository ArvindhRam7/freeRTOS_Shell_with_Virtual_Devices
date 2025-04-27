#include "SolarPanel.h"


const float SolarPanel::VOLTAGE = 18.0f;
const float SolarPanel::MAX_CURRENT = 2.0f;

// Constructor to initialize the current hour
SolarPanel::SolarPanel(int currentHour) : hour(currentHour) {}

// Function to calculate solar intensity based on the current hour (0-23)
float SolarPanel::calculateSolarIntensity() {
    // Intensity is zero before 6 AM and after 6 PM
    if (hour < 6 || hour > 18) {
        return 0.0f;
    }

    // Use a sine curve to model the intensity between 6 AM and 6 PM
    return std::sin((2 * M_PI / 12) * (hour - 6));  // 12 hours between 6 AM and 6 PM
}

// Function to calculate solar current based on intensity
float SolarPanel::calculateSolarCurrent() {
    // Calculate intensity using sine curve
    float intensity = calculateSolarIntensity();

    // Scale intensity to the max current (0A to MAX_CURRENT)
    return MAX_CURRENT * intensity;
}

// Function to calculate solar power
float SolarPanel::calculateSolarPower() {
    // Power = Voltage * Current
    return VOLTAGE * calculateSolarCurrent();
}

