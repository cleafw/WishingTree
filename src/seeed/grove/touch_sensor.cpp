//
// Grove 触摸传感器 (TTP223) 驱动实现
//

#include "touch_sensor.h"

TouchSensor::TouchSensor(uint8_t pin)
    : touchPin(pin), lastState(false) {
}

void TouchSensor::begin() {
    pinMode(touchPin, INPUT);
    lastState = digitalRead(touchPin);
}

bool TouchSensor::isTouched() {
    return digitalRead(touchPin) == HIGH;
}

bool TouchSensor::isPressed() {
    bool current = isTouched();
    bool pressed = (current && !lastState);
    lastState = current;
    return pressed;
}

bool TouchSensor::isReleased() {
    bool current = isTouched();
    bool released = (!current && lastState);
    lastState = current;
    return released;
}
