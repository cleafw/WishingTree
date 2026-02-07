//
// Grove 集成压力传感器 (MPX5700AP) 驱动实现
//

#include "pressure_sensor.h"

PressureSensor::PressureSensor(uint8_t pin, int offsetVal, int fullScaleVal, float maxKpa)
    : analogPin(pin), offset(offsetVal), fullScale(fullScaleVal), maxPressure(maxKpa) {
}

void PressureSensor::begin() {
    pinMode(analogPin, INPUT);
}

int PressureSensor::readRaw() {
    int sum = 0;
    for (int i = 0; i < PRESSURE_SAMPLE_COUNT; i++) {
        sum += analogRead(analogPin);
    }
    return sum;
}

float PressureSensor::readPressure() {
    int raw = readRaw();
    float pressure = (float)(raw - offset) * maxPressure / (float)(fullScale - offset);
    if (pressure < 0) pressure = 0;
    return pressure;
}

void PressureSensor::calibrate(int offsetVal, int fullScaleVal) {
    offset    = offsetVal;
    fullScale = fullScaleVal;
}
