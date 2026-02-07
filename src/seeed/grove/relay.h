//
// Created by seeed on 25-8-15.
//

#ifndef RELAY_H
#define RELAY_H

#include <Arduino.h>

// 继电器类
class Relay {
private:
    uint8_t relay_pin;

public:
    explicit Relay(uint8_t pin);
    
    // 打开继电器
    void on() const;
    
    // 关闭继电器
    void off() const;
    
    // 切换继电器状态
    void toggle() const;
    
    // 检查继电器是否打开
    bool isOn() const;
};

#endif //RELAY_H