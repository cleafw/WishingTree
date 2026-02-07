//
// Created by 99081 on 2026/2/6.
//

#ifndef WISHINGTREE_GDATA_H
#define WISHINGTREE_GDATA_H

#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

// ==================== 引脚定义 ====================
#define StripLight_PIN_0    D0      // 灯带 0 数据引脚
#define StripLight_PIN_1    D1      // 灯带 1 数据引脚
#define StripLight_PIN_2    D2      // 灯带 2 数据引脚
#define StripLight_PIN_3    D5      // 灯带 3 数据引脚
#define Relay_PIN           D9      // 继电器数字引脚
#define TouchSensor_PIN     D8      // 触摸传感器数字引脚

// ==================== 灯带配置 ====================
#define STRIP_COUNT         4       // 灯带数量
#define STRIP_NUM_LEDS      200     // 每条灯带 LED 数量
#define STRIP_BRIGHTNESS    255     // 灯带默认亮度
#define STRIP_COLOR_R       250     // 灯带固定颜色 R
#define STRIP_COLOR_G       40      // 灯带固定颜色 G
#define STRIP_COLOR_B       0       // 灯带固定颜色 B

// ==================== 呼吸灯配置 ====================
#define BREATHE_STEP_MS     10      // 呼吸灯每步间隔 (ms)
#define BREATHE_MIN         10      // 呼吸灯最低亮度
#define BREATHE_MAX         255     // 呼吸灯最高亮度

// ==================== FreeRTOS 任务配置 ====================
#define TASK_MAIN_STACK     16384
#define TASK_MAIN_PRIORITY  1

// ==================== 看门狗配置 ====================
#define WDT_TIMEOUT_S       10      // 看门狗超时 (秒)

#endif //WISHINGTREE_GDATA_H
