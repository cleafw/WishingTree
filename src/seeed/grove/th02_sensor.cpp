//
// Grove 温湿度传感器 (TH02) 驱动实现
//

#include "th02_sensor.h"

TH02Sensor::TH02Sensor(uint8_t addr) : i2cAddr(addr) {
}

void TH02Sensor::begin() {
    Wire.begin();
}

void TH02Sensor::writeReg(uint8_t reg, uint8_t value) {
    Wire.beginTransmission(i2cAddr);
    Wire.write(reg);
    Wire.write(value);
    Wire.endTransmission();
}

uint8_t TH02Sensor::readReg(uint8_t reg) {
    Wire.beginTransmission(i2cAddr);
    Wire.write(reg);
    Wire.endTransmission();
    Wire.requestFrom(i2cAddr, (uint8_t)1);
    return Wire.available() ? Wire.read() : 0;
}

uint16_t TH02Sensor::readData() {
    Wire.beginTransmission(i2cAddr);
    Wire.write(TH02_REG_DATA_H);
    Wire.endTransmission();
    Wire.requestFrom(i2cAddr, (uint8_t)2);
    if (Wire.available() >= 2) {
        uint8_t msb = Wire.read();
        uint8_t lsb = Wire.read();
        return ((uint16_t)msb << 8) | lsb;
    }
    return 0;
}

bool TH02Sensor::waitForReady(uint32_t timeoutMs) {
    uint32_t start = millis();
    while (millis() - start < timeoutMs) {
        if (!(readReg(TH02_REG_STATUS) & TH02_STATUS_RDY_MASK)) {
            return true;  // 测量完成
        }
        delay(5);
    }
    return false;  // 超时
}

float TH02Sensor::readTemperature() {
    writeReg(TH02_REG_CONFIG, TH02_CMD_MEASURE_TEMP);
    if (!waitForReady()) return -999.0f;

    uint16_t raw = readData();
    raw >>= 2;  // 去掉低 2 位
    return (float)raw / 32.0f - 50.0f;
}

float TH02Sensor::readHumidity() {
    writeReg(TH02_REG_CONFIG, TH02_CMD_MEASURE_HUMI);
    if (!waitForReady()) return -999.0f;

    uint16_t raw = readData();
    raw >>= 4;  // 去掉低 4 位
    return (float)raw / 16.0f - 24.0f;
}
