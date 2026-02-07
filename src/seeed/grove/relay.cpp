//
// Created by seeed on 25-8-15.
//

#include "relay.h"
#include <Arduino.h>

// 继电器类构造函数
Relay::Relay(uint8_t pin) : relay_pin(pin) {
    pinMode(relay_pin, OUTPUT);
    digitalWrite(relay_pin, LOW); // 默认关闭继电器
}

// 打开继电器
void Relay::on() const {
    digitalWrite(relay_pin, HIGH);
}

// 关闭继电器
void Relay::off() const {
    digitalWrite(relay_pin, LOW);
}

// 切换继电器状态
void Relay::toggle() const {
    digitalWrite(relay_pin, !digitalRead(relay_pin));
}

// 检查继电器是否打开
bool Relay::isOn() const {
    return digitalRead(relay_pin) == HIGH;
}