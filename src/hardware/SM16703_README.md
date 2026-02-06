# SM16703 LED灯带驱动库

## 📁 文件说明

- `sm16703_strip.h` - 头文件
- `sm16703_strip.cpp` - 实现文件
- `sm16703_examples.ino` - 示例代码（6个完整示例）

## 🚀 快速开始

### 1. 安装库

将 `sm16703_strip.h` 和 `sm16703_strip.cpp` 复制到你的Arduino项目文件夹

### 2. 基础示例

```cpp
#include "sm16703_strip.h"

SM16703Strip strip(D4, 201);  // 数据引脚D4, 201个LED

void setup() {
    strip.begin();
    strip.setBrightness(100);
}

void loop() {
    strip.rainbow(20);  // 彩虹效果
}
```

## 📖 API速查

### 初始化
```cpp
// 只需数据引脚
SM16703Strip strip(D4, 201);

// 带电源控制引脚(如果硬件有MOSFET)
SM16703Strip strip(D4, D0, 201, true);

strip.begin();                  // 初始化
strip.setBrightness(100);       // 设置亮度0-255
```

### 颜色控制
```cpp
strip.setPixelColor(0, 255, 0, 0);     // 单个LED红色
strip.fillColor(0, 255, 0);            // 全部绿色
strip.fillRange(0, 10, 0, 0, 255);     // 前10个蓝色
strip.show();                          // 刷新显示(必须调用)
```

### 特效
```cpp
strip.rainbow(20);                      // 彩虹
strip.breathe(255, 0, 0, 10);          // 红色呼吸灯
strip.theaterChase(0, 255, 0, 50);     // 绿色追逐
strip.scanner(255, 0, 0, 10, 30);      // 红色扫描
strip.flow(0, 255, 255, 10, 30);       // 青色流水
strip.fire();                           // 火焰效果
strip.lightning(3);                     // 闪电效果
strip.gradientFill(255,0,0, 0,0,255);  // 红到蓝渐变
```

## 🎯 示例说明

### 示例1: 基础颜色控制
展示如何设置不同颜色

### 示例2: 霍尔传感器控制
每次检测到磁铁点亮5个LED，全亮后等待3秒重置

### 示例3: 触摸传感器呼吸灯
触摸时呼吸效果，松开时常亮

### 示例4: 炫酷特效展示
循环播放彩虹、追逐、扫描、流水、火焰、闪电、呼吸等特效

### 示例5: 渐变颜色
展示各种颜色渐变效果

### 示例6: 自定义动画
使用波浪、多色波、追逐等自定义动画

## ⚙️ 硬件连接

### 标准连接
```
ESP32-C3    SM16703灯带
  D4   ---->  DIN
  GND  ---->  GND
  5V   ---->  VCC
```

### 带电源控制
```
ESP32-C3    MOSFET      SM16703灯带
  D4   ------------------> DIN
  D0   ---> Gate
  GND  ---> Source -----> GND
  5V   ----------> Drain -> VCC
```

## ⚠️ 注意事项

1. **必须调用show()**: 所有颜色设置后都要调用`strip.show()`
2. **RGB顺序**: SM16703是RGB顺序(不是GRB)
3. **电源**: 每个LED约60mA，201个LED最大约12A
4. **亮度**: 建议100-200，最大255很刺眼

## 💡 使用技巧

### 霍尔传感器防抖
```cpp
void IRAM_ATTR hallInterrupt() {
    static unsigned long lastTime = 0;
    if (millis() - lastTime > 200) {  // 200ms防抖
        hallTriggered = true;
        lastTime = millis();
    }
}
```

### 触摸传感器防抖
```cpp
static unsigned long lastDebounce = 0;
if (millis() - lastDebounce > 50) {  // 50ms防抖
    // 处理触摸
    lastDebounce = millis();
}
```

### 直接操作LED数组
```cpp
CRGB* leds = strip.getLEDs();
for(int i = 0; i < strip.numPixels(); i++) {
    leds[i] = CRGB(255, 0, 0);  // 直接设置
}
strip.show();
```

## 🔧 常见问题

**Q: 灯带不亮？**
- 检查`begin()`是否调用
- 检查`show()`是否调用
- 检查接线是否正确

**Q: 颜色不对？**
- SM16703是RGB顺序
- 检查电源是否充足

**Q: 闪烁？**
- 降低特效速度参数
- 检查电源质量

## 📞 技术支持

如有问题，请检查：
1. 引脚定义是否正确
2. FastLED库是否安装
3. 电源是否充足
4. 接线是否牢固
