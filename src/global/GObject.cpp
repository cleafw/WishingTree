//
// 全局对象管理实现
//

#include "GObject.h"

// 4条灯带实例
WS2813Ring strip0(StripLight_PIN_0, STRIP_NUM_LEDS);
WS2813Ring strip1(StripLight_PIN_1, STRIP_NUM_LEDS);
WS2813Ring strip2(StripLight_PIN_2, STRIP_NUM_LEDS);
WS2813Ring strip3(StripLight_PIN_3, STRIP_NUM_LEDS);
WS2813Ring* strips[STRIP_COUNT] = {&strip0, &strip1, &strip2, &strip3};

// 触摸传感器
TouchSensor touchSensor(TouchSensor_PIN);

// 继电器
Relay relay(Relay_PIN);
