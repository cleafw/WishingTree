//
// Grove 集成压力传感器 (MPX5700AP) 驱动头文件
// 量程: 15 kPa - 700 kPa
// 接口: 模拟输出 (ADC)
//

#ifndef PRESSURE_SENSOR_H
#define PRESSURE_SENSOR_H

#include <Arduino.h>

// 采样次数（取平均值降噪）
#define PRESSURE_SAMPLE_COUNT  10

// 校准默认值（基于 Arduino 10-bit ADC, 5V 参考）
// 实际使用时需根据 ESP32 的 ADC 特性重新校准
#define PRESSURE_DEFAULT_OFFSET     410
#define PRESSURE_DEFAULT_FULLSCALE  9630

class PressureSensor {
private:
    uint8_t  analogPin;       // 模拟输入引脚
    int      offset;          // 零压偏移值 (N次采样之和)
    int      fullScale;       // 满量程值   (N次采样之和)
    float    maxPressure;     // 最大量程 kPa

public:
    // 构造函数
    explicit PressureSensor(uint8_t pin,
                            int offsetVal    = PRESSURE_DEFAULT_OFFSET,
                            int fullScaleVal = PRESSURE_DEFAULT_FULLSCALE,
                            float maxKpa     = 700.0f);

    // 初始化
    void begin();

    // 读取原始 ADC 累加值（N 次采样之和）
    int readRaw();

    // 读取压力值，单位 kPa
    float readPressure();

    // 重新设置校准参数
    void calibrate(int offsetVal, int fullScaleVal);
};

#endif // PRESSURE_SENSOR_H
