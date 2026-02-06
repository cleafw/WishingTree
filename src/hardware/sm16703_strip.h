/**
 * @file sm16703_strip.h
 * @brief SM16703 LED灯带驱动库
 * 
 * SM16703是单线协议的可寻址LED驱动芯片
 * 引脚: DIN(数据输入), DOUT(数据输出), VCC, GND
 * 注意: SM16703没有独立的OE使能引脚
 */

#ifndef SM16703_STRIP_H
#define SM16703_STRIP_H

#include <Arduino.h>
#include <FastLED.h>

#define SM16703_DEFAULT_NUM_LEDS 201                    // 默认LED数量

class SM16703Strip {
private:
    CRGB* leds;                                         // LED数组指针
    uint16_t numLEDs;                                   // LED总数量
    uint8_t dataPin;                                    // 数据引脚
    uint8_t powerPin;                                   // 电源控制引脚(可选)
    bool hasPowerControl;                               // 是否启用电源控制
    uint8_t brightness;                                 // 全局亮度(0-255)

public:
    // ==================== 构造函数 ====================

    SM16703Strip(uint8_t dataPin,                       // 只需数据引脚的构造函数
                 uint16_t numPixels = SM16703_DEFAULT_NUM_LEDS);

    SM16703Strip(uint8_t dataPin,                       // 带电源控制引脚的构造函数
                 uint8_t powerPin,
                 uint16_t numPixels,
                 bool usePowerControl);

    ~SM16703Strip();                                    // 析构函数，释放内存

    // ==================== 基础控制 ====================

    void begin();                                       // 初始化灯带(必须首先调用)
    void setBrightness(uint8_t bright);                 // 设置全局亮度(0-255)
    void clear();                                       // 清空所有LED(设为黑色)
    void show();                                        // 刷新显示(必须调用才能看到效果)

    // ==================== 电源控制 ====================

    void powerOn();                                     // 打开电源(需要powerPin)
    void powerOff();                                    // 关闭电源(需要powerPin)

    // ==================== 颜色设置 ====================

    void setPixelColor(uint16_t n,                      // 设置单个LED颜色(RGB值)
                       uint8_t r, uint8_t g, uint8_t b);

    void setPixelColor(uint16_t n,                      // 设置单个LED颜色(CRGB对象)
                       CRGB color);

    void fillColor(uint8_t r, uint8_t g, uint8_t b);   // 填充所有LED为相同颜色(RGB值)

    void fillColor(CRGB color);                         // 填充所有LED为相同颜色(CRGB对象)

    void fillRange(uint16_t start,                      // 填充指定范围LED(RGB值)
                   uint16_t count,
                   uint8_t r, uint8_t g, uint8_t b);

    void fillRange(uint16_t start,                      // 填充指定范围LED(CRGB对象)
                   uint16_t count,
                   CRGB color);

    // ==================== 基础特效 ====================

    void colorWipe(uint8_t r, uint8_t g, uint8_t b,    // 颜色擦除效果(逐个点亮)
                   uint8_t wait = 50);

    void colorWipe(CRGB color,                          // 颜色擦除效果(CRGB对象)
                   uint8_t wait = 50);

    void rainbow(uint8_t wait = 20);                    // 彩虹效果(循环显示彩虹色)

    void rainbowCycle(uint8_t wait = 20,                // 彩虹循环效果(可设置循环次数)
                      uint8_t cycles = 5);

    void blink(uint8_t r, uint8_t g, uint8_t b,        // 闪烁效果(指定次数和间隔)
               uint8_t times = 3,
               uint16_t interval = 500);

    void blink(CRGB color,                              // 闪烁效果(CRGB对象)
               uint8_t times = 3,
               uint16_t interval = 500);

    // ==================== 动态特效 ====================

    void theaterChase(uint8_t r, uint8_t g, uint8_t b, // 剧院追逐效果(每隔3个LED点亮)
                      uint8_t wait = 50);

    void theaterChase(CRGB color,                       // 剧院追逐效果(CRGB对象)
                      uint8_t wait = 50);

    void theaterChaseRainbow(uint8_t wait = 50);        // 彩虹剧院追逐效果

    void breathe(uint8_t r, uint8_t g, uint8_t b,      // 呼吸灯效果(渐亮渐暗)
                 uint8_t wait = 10);

    void breathe(CRGB color,                            // 呼吸灯效果(CRGB对象)
                 uint8_t wait = 10);

    void rotate(uint8_t r, uint8_t g, uint8_t b,       // 旋转效果(单点旋转)
                uint8_t wait = 50);

    void rotate(CRGB color,                             // 旋转效果(CRGB对象)
                uint8_t wait = 50);

    void flow(uint8_t r, uint8_t g, uint8_t b,         // 流水效果(带尾巴的移动光点)
              uint8_t length = 5,
              uint8_t wait = 30);

    void flow(CRGB color,                               // 流水效果(CRGB对象)
              uint8_t length = 5,
              uint8_t wait = 30);

    void scanner(uint8_t r, uint8_t g, uint8_t b,      // 扫描效果(K.I.T.T.效果,来回扫描)
                 uint8_t width = 5,
                 uint8_t wait = 30);

    void scanner(CRGB color,                            // 扫描效果(CRGB对象)
                 uint8_t width = 5,
                 uint8_t wait = 30);

    // ==================== 高级特效 ====================

    void gradientFill(uint8_t r1, uint8_t g1, uint8_t b1,  // 渐变填充(从颜色1到颜色2)
                      uint8_t r2, uint8_t g2, uint8_t b2);

    void gradientFill(CRGB color1,                      // 渐变填充(CRGB对象)
                      CRGB color2);

    void fire(uint8_t cooling = 55,                     // 火焰效果(模拟火焰燃烧)
              uint8_t sparking = 120,
              uint8_t wait = 15);

    void lightning(uint8_t flashes = 3);                // 闪电效果(模拟闪电闪烁)

    // ==================== 工具函数 ====================

    uint16_t numPixels() const;                         // 获取LED总数量

    CRGB getPixelColor(uint16_t n) const;               // 获取指定LED的颜色

    CRGB* getLEDs();                                    // 获取LED数组指针(高级用法)

private:
    CRGB wheel(uint8_t wheelPos);                       // 色轮函数(生成彩虹色)
};

#endif

/*
 * ==================== 快速使用指南 ====================
 *
 * 1. 基础使用(只需数据引脚):
 *    SM16703Strip strip(D4, 201);
 *    strip.begin();
 *    strip.setBrightness(100);
 *    strip.fillColor(255, 0, 0);
 *    strip.show();
 *
 * 2. 带电源控制:
 *    SM16703Strip strip(D4, D0, 201, true);
 *    strip.begin();
 *    strip.powerOn();
 *    strip.setBrightness(100);
 *
 * 3. 特效示例:
 *    strip.rainbow(20);              // 彩虹
 *    strip.breathe(255, 0, 0, 10);   // 红色呼吸
 *    strip.scanner(0, 255, 0, 10);   // 绿色扫描
 *    strip.fire();                    // 火焰
 *    strip.lightning(5);              // 闪电
 *
 * 4. 常用颜色(CRGB):
 *    CRGB::Red        // 红色
 *    CRGB::Green      // 绿色
 *    CRGB::Blue       // 蓝色
 *    CRGB::Yellow     // 黄色
 *    CRGB::Purple     // 紫色
 *    CRGB::Cyan       // 青色
 *    CRGB::White      // 白色
 *    CRGB::Black      // 黑色
 *
 * 5. 参数说明:
 *    - wait: 延时(毫秒), 数值越小速度越快
 *    - times: 重复次数
 *    - interval: 间隔时间(毫秒)
 *    - length: 长度(LED数量)
 *    - width: 宽度(LED数量)
 *    - cooling: 冷却速度(0-255)
 *    - sparking: 火花密度(0-255)
 *    - cycles: 循环次数
 *
 * ==================== 注意事项 ====================
 *
 * 1. 必须调用show()才能看到效果
 * 2. SM16703的RGB顺序是RGB(不是GRB)
 * 3. 建议亮度设置在100-200之间
 * 4. 每个LED约60mA, 注意电源容量
 * 5. 数据引脚支持: D0-D10
 */