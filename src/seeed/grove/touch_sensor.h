//
// Grove 触摸传感器 (TTP223) 驱动头文件
// 芯片: TTP223-BA6
// 工作电压: 2.0 - 5.5V
// 接口: 数字输入，触摸时输出高电平
//

#ifndef TOUCH_SENSOR_H
#define TOUCH_SENSOR_H

#include <Arduino.h>

class TouchSensor {
private:
    uint8_t touchPin;       // 数字输入引脚
    bool    lastState;      // 上一次状态（用于边沿检测）

public:
    // 构造函数
    explicit TouchSensor(uint8_t pin);

    // 初始化
    void begin();

    // 读取当前触摸状态: true = 被触摸, false = 未触摸
    bool isTouched();

    // 检测是否刚被按下（上升沿），需要在循环中持续调用
    bool isPressed();

    // 检测是否刚被释放（下降沿），需要在循环中持续调用
    bool isReleased();
};

#endif // TOUCH_SENSOR_H
