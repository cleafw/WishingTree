//
// Grove 温湿度传感器 (TH02) 驱动头文件
// 通信: I2C  地址: 0x40
// 量程: 温度 -40~85°C, 湿度 0~100%RH
//

#ifndef TH02_SENSOR_H
#define TH02_SENSOR_H

#include <Arduino.h>
#include <Wire.h>

// I2C 地址
#define TH02_I2C_ADDR       0x40

// 寄存器地址
#define TH02_REG_STATUS     0x00
#define TH02_REG_DATA_H     0x01
#define TH02_REG_DATA_L     0x02
#define TH02_REG_CONFIG     0x03
#define TH02_REG_ID         0x11

// 测量命令
#define TH02_CMD_MEASURE_TEMP  0x11   // 启动温度测量
#define TH02_CMD_MEASURE_HUMI  0x01   // 启动湿度测量

// 状态位
#define TH02_STATUS_RDY_MASK   0x01   // 0=测量完成, 1=测量中

class TH02Sensor {
private:
    uint8_t i2cAddr;

    // I2C 底层操作
    void     writeReg(uint8_t reg, uint8_t value);
    uint8_t  readReg(uint8_t reg);
    uint16_t readData();

    // 等待测量完成
    bool waitForReady(uint32_t timeoutMs = 100);

public:
    explicit TH02Sensor(uint8_t addr = TH02_I2C_ADDR);

    // 初始化
    void begin();

    // 读取温度 (°C)
    float readTemperature();

    // 读取湿度 (%RH)
    float readHumidity();
};

#endif // TH02_SENSOR_H
