#include <Arduino.h>
#include "hardware/sm16703_strip.h"

// ==================== 全局配置 ====================
#define DATA_PIN    D0
#define NUM_LEDS    200

SM16703Strip strip(DATA_PIN, NUM_LEDS);

void setup() {
    Serial.begin(115200);
    Serial.println("示例1: 基础颜色控制");

    strip.begin();
    strip.setBrightness(255);
    strip.clear();
    strip.show();  // ✅ 必须调用show()才能真正清空
    delay(1000);
}

void loop() {
    // 逐个点亮红色
    for (int i = 0; i < strip.numPixels(); i++) {
        strip.clear();              // 每次清空
        strip.setPixelColor(i, 255, 0, 0);  // 点亮当前LED
        strip.show();               // 刷新
        delay(50);                  // 延时50ms
    }
}