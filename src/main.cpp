#include <Arduino.h>
#include "seeed/grove/ws2813_ring.h"
#include "global/GData.h"
#include "global/GObject.h"

// ==================== 全局配置 ====================
#define NUM_LEDS    200

void setup() {
    Serial.begin(115200);
    Serial.println("呼吸灯测试");

    strip0.begin();
    strip0.setBrightness(255);
    strip0.clear();
    strip0.fillColor(255, 0, 0);
    strip0.show();
}

void loop() {
    strip0.fillColor(255, 0, 0);
    strip0.show();
    delay(1000);
    strip0.fillColor(0, 255, 0);
    strip0.show();
    delay(1000);
    strip0.fillColor(0, 0, 255);
    strip0.show();
    delay(1000);
    for(int i = 0; i < NUM_LEDS; i ++){
        strip0.setPixelColor(i, 255, 255, 255);
        strip0.show();
        delay(100);
    }
    delay(1000);
}