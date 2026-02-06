/**
 * @file sm16703_examples.ino
 * @brief SM16703驱动使用示例集合
 * 
 * 包含6个完整示例:
 * 1. 基础颜色控制
 * 2. 霍尔传感器控制灯带
 * 3. 触摸传感器呼吸灯
 * 4. 炫酷特效展示
 * 5. 渐变颜色
 * 6. 自定义动画
 */

#include "sm16703_strip.h"

// ==================== 全局配置 ====================
#define DATA_PIN    D4
#define POWER_PIN   D0
#define HALL_PIN    D7
#define TOUCH_PIN   D7
#define NUM_LEDS    201

// ==================== 选择示例 ====================
// 取消注释要运行的示例
// #define RUN_EXAMPLE_1    // 基础颜色控制
// #define RUN_EXAMPLE_2    // 霍尔传感器控制
// #define RUN_EXAMPLE_3    // 触摸呼吸灯
#define RUN_EXAMPLE_4    // 炫酷特效
// #define RUN_EXAMPLE_5    // 渐变颜色
// #define RUN_EXAMPLE_6    // 自定义动画

// ==================== 示例1: 基础颜色控制 ====================
#ifdef RUN_EXAMPLE_1

SM16703Strip strip(DATA_PIN, NUM_LEDS);

void setup() {
    Serial.begin(115200);
    Serial.println("示例1: 基础颜色控制");
    
    strip.begin();
    strip.setBrightness(100);
}

void loop() {
    // 红色
    Serial.println("红色");
    strip.fillColor(255, 0, 0);
    strip.show();
    delay(1000);
    
    // 绿色
    Serial.println("绿色");
    strip.fillColor(0, 255, 0);
    strip.show();
    delay(1000);
    
    // 蓝色
    Serial.println("蓝色");
    strip.fillColor(0, 0, 255);
    strip.show();
    delay(1000);
    
    // 黄色
    Serial.println("黄色");
    strip.fillColor(255, 255, 0);
    strip.show();
    delay(1000);
    
    // 紫色
    Serial.println("紫色");
    strip.fillColor(255, 0, 255);
    strip.show();
    delay(1000);
    
    // 青色
    Serial.println("青色");
    strip.fillColor(0, 255, 255);
    strip.show();
    delay(1000);
    
    // 白色
    Serial.println("白色");
    strip.fillColor(255, 255, 255);
    strip.show();
    delay(1000);
    
    // 清空
    Serial.println("清空");
    strip.clear();
    strip.show();
    delay(1000);
}

#endif

// ==================== 示例2: 霍尔传感器控制 ====================
#ifdef RUN_EXAMPLE_2

SM16703Strip strip(DATA_PIN, NUM_LEDS);

volatile bool hallTriggered = false;
int currentLedCount = 0;
const int LED_GROUP_NUM = 5;

void IRAM_ATTR hallInterrupt() {
    static unsigned long lastTime = 0;
    unsigned long now = millis();
    
    // 防抖: 200ms内的触发忽略
    if (now - lastTime > 200) {
        hallTriggered = true;
        lastTime = now;
    }
}

void setup() {
    Serial.begin(115200);
    Serial.println("示例2: 霍尔传感器控制");
    Serial.println("每次检测到磁铁点亮5个LED");
    
    // 初始化灯带
    strip.begin();
    strip.setBrightness(100);
    
    // 初始化霍尔传感器
    pinMode(HALL_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(HALL_PIN), hallInterrupt, CHANGE);
    
    Serial.println("系统就绪，等待霍尔传感器触发...");
}

void loop() {
    if (hallTriggered) {
        hallTriggered = false;
        
        // 增加点亮的LED数量
        currentLedCount += LED_GROUP_NUM;
        if (currentLedCount > strip.numPixels()) {
            currentLedCount = strip.numPixels();
        }
        
        // 更新显示
        strip.clear();
        strip.fillRange(0, currentLedCount, 255, 30, 0); // 橙黄色
        strip.show();
        
        Serial.print("检测到磁铁 | 当前点亮LED数: ");
        Serial.println(currentLedCount);
        
        // 如果全亮，等待3秒后重置
        if (currentLedCount >= strip.numPixels()) {
            Serial.println("全亮! 3秒后重置...");
            delay(3000);
            currentLedCount = 0;
            strip.clear();
            strip.show();
            Serial.println("已重置");
        }
    }
    delay(10);
}

#endif

// ==================== 示例3: 触摸传感器呼吸灯 ====================
#ifdef RUN_EXAMPLE_3

SM16703Strip strip(DATA_PIN, NUM_LEDS);

void setup() {
    Serial.begin(115200);
    Serial.println("示例3: 触摸控制呼吸灯");
    Serial.println("触摸时呼吸效果，松开时常亮");
    
    strip.begin();
    strip.setBrightness(255);
    pinMode(TOUCH_PIN, INPUT);
}

void loop() {
    static unsigned long lastDebounce = 0;
    static bool lastTouchState = false;
    
    bool currentTouch = (digitalRead(TOUCH_PIN) == HIGH);
    
    // 简单防抖
    if (millis() - lastDebounce > 50) {
        if (currentTouch != lastTouchState) {
            lastTouchState = currentTouch;
            lastDebounce = millis();
            
            if (currentTouch) {
                Serial.println("触摸检测到 - 呼吸灯模式");
            } else {
                Serial.println("触摸释放 - 常亮模式");
            }
        }
    }
    
    if (lastTouchState) {
        // 触摸时: 橙红色呼吸
        strip.breathe(255, 40, 0, 5);
    } else {
        // 不触摸时: 橙红色常亮
        strip.fillColor(255, 40, 0);
        strip.show();
        delay(10);
    }
}

#endif

// ==================== 示例4: 炫酷特效展示 ====================
#ifdef RUN_EXAMPLE_4

SM16703Strip strip(DATA_PIN, NUM_LEDS);

void setup() {
    Serial.begin(115200);
    Serial.println("示例4: 炫酷特效展示");
    Serial.println("循环播放各种特效");
    
    strip.begin();
    strip.setBrightness(150);
}

void loop() {
    // 彩虹效果
    Serial.println("特效: 彩虹");
    strip.rainbow(20);
    delay(500);
    
    // 红色剧院追逐
    Serial.println("特效: 红色追逐");
    strip.theaterChase(255, 0, 0, 50);
    delay(500);
    
    // 绿色追逐
    Serial.println("特效: 绿色追逐");
    strip.theaterChase(0, 255, 0, 50);
    delay(500);
    
    // 蓝色追逐
    Serial.println("特效: 蓝色追逐");
    strip.theaterChase(0, 0, 255, 50);
    delay(500);
    
    // 扫描效果
    Serial.println("特效: 红色扫描");
    strip.scanner(255, 0, 0, 10, 30);
    delay(500);
    
    // 青色流水
    Serial.println("特效: 青色流水");
    strip.flow(0, 255, 255, 10, 30);
    delay(500);
    
    // 火焰效果
    Serial.println("特效: 火焰");
    strip.fire(55, 120, 15);
    delay(500);
    
    // 闪电效果
    Serial.println("特效: 闪电");
    strip.clear();
    strip.show();
    delay(1000);
    strip.lightning(3);
    delay(1000);
    
    // 蓝色呼吸
    Serial.println("特效: 蓝色呼吸");
    strip.breathe(0, 0, 255, 8);
    delay(500);
}

#endif

// ==================== 示例5: 渐变颜色 ====================
#ifdef RUN_EXAMPLE_5

SM16703Strip strip(DATA_PIN, NUM_LEDS);

void setup() {
    Serial.begin(115200);
    Serial.println("示例5: 渐变颜色");
    
    strip.begin();
    strip.setBrightness(200);
}

void loop() {
    // 红到蓝渐变
    Serial.println("红到蓝渐变");
    strip.gradientFill(255, 0, 0, 0, 0, 255);
    strip.show();
    delay(2000);
    
    // 绿到紫渐变
    Serial.println("绿到紫渐变");
    strip.gradientFill(0, 255, 0, 255, 0, 255);
    strip.show();
    delay(2000);
    
    // 黄到青渐变
    Serial.println("黄到青渐变");
    strip.gradientFill(255, 255, 0, 0, 255, 255);
    strip.show();
    delay(2000);
    
    // 橙到蓝渐变
    Serial.println("橙到蓝渐变");
    strip.gradientFill(255, 100, 0, 0, 100, 255);
    strip.show();
    delay(2000);
    
    // 白到黑渐变
    Serial.println("白到黑渐变");
    strip.gradientFill(255, 255, 255, 0, 0, 0);
    strip.show();
    delay(2000);
}

#endif

// ==================== 示例6: 自定义动画 ====================
#ifdef RUN_EXAMPLE_6

SM16703Strip strip(DATA_PIN, NUM_LEDS);

void setup() {
    Serial.begin(115200);
    Serial.println("示例6: 自定义波浪动画");
    
    strip.begin();
    strip.setBrightness(150);
}

void loop() {
    // 获取LED数组直接操作
    CRGB* leds = strip.getLEDs();
    
    // 波浪效果1: 正弦波
    Serial.println("波浪动画1");
    for (int j = 0; j < 360; j++) {
        for (int i = 0; i < strip.numPixels(); i++) {
            float angle = (i * 10 + j) * 3.14159 / 180.0;
            uint8_t brightness = (sin(angle) + 1) * 127;
            leds[i] = CRGB(brightness, 0, 255 - brightness);
        }
        strip.show();
        delay(20);
    }
    
    // 波浪效果2: 多色波
    Serial.println("波浪动画2");
    for (int j = 0; j < 360; j++) {
        for (int i = 0; i < strip.numPixels(); i++) {
            float angle1 = (i * 5 + j) * 3.14159 / 180.0;
            float angle2 = (i * 7 + j * 2) * 3.14159 / 180.0;
            float angle3 = (i * 9 + j * 3) * 3.14159 / 180.0;
            
            uint8_t r = (sin(angle1) + 1) * 127;
            uint8_t g = (sin(angle2) + 1) * 127;
            uint8_t b = (sin(angle3) + 1) * 127;
            
            leds[i] = CRGB(r, g, b);
        }
        strip.show();
        delay(20);
    }
    
    // 追逐效果
    Serial.println("追逐动画");
    for (int round = 0; round < 3; round++) {
        for (int i = 0; i < strip.numPixels(); i++) {
            strip.clear();
            
            // 点亮当前位置及尾部
            for (int j = 0; j < 10; j++) {
                int pos = i - j;
                if (pos >= 0) {
                    uint8_t brightness = 255 - (j * 25);
                    leds[pos] = CRGB(0, brightness, brightness);
                }
            }
            
            strip.show();
            delay(30);
        }
    }
}

#endif
