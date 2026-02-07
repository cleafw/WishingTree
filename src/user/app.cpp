//
// Created by 99081 on 2026/2/7.
//

#include "app.h"

//灯带测试
void strips_Test() {
    for (int i = 0; i < STRIP_COUNT; i++) {
        strips[i]->setBrightness(STRIP_BRIGHTNESS);
        strips[i]->fillColor(STRIP_COLOR_R, STRIP_COLOR_G, STRIP_COLOR_B);
        strips[i]->show();

        for (int i = 0; i < STRIP_COUNT; i++){
            strips[i]->fillColor(255, 0, 0);
            strips[i]->show();
        }
        delay(1000);

        for (int i = 0; i < STRIP_COUNT; i++){
            strips[i]->fillColor(0, 255, 0);
            strips[i]->show();
        }
        delay(1000);
        for (int i = 0; i < STRIP_COUNT; i++){
            strips[i]->fillColor(0, 0, 255);
            strips[i]->show();
        }
        delay(1000);

        for(int n = 0; n < STRIP_NUM_LEDS; n ++){
            for(int i = 0; i < STRIP_COUNT; i ++){
                strips[i]->setPixelColor(n, 255, 255, 255);
                strips[i]->show();
            }
            delay(50);
        }
        delay(1000);
    }
}

// 触摸测试
void touch_Test() {
    uint8_t touched = touchSensor.isTouched();
    printf("Touched: %d\n", touched);
    delay(300);
}

// 灯带打开
void strips_On() {
    for (int i = 0; i < STRIP_COUNT; i++) {
        strips[i]->setBrightness(255);
        strips[i]->fillColor(STRIP_COLOR_G, STRIP_COLOR_R, STRIP_COLOR_B);
        strips[i]->setBrightness(STRIP_BRIGHTNESS);
    }
    for (int i = 0; i < STRIP_COUNT; i++) {
        strips[i]->show();
    }
}

// 继电器控制(限制继电器打开时长)
uint32_t relay_count = 0;   // 触摸程序循环计数
void relay_Control() {
    if(touchSensor.isTouched() && relay_count < RELAY_COUNT_MAX){   // 触摸 并且没有超时
        relay.on();             // 继电器开
        relay_count ++;
        printf("relay_count: %d\n", relay_count);
    }else if(relay_count != 0 && relay_count < RELAY_COUNT_MIN){    // 触摸太短延长时间
        relay_count ++;
        printf("relay_count: %d\n", relay_count);
    }else if(!touchSensor.isTouched()){
        relay.off();            // 继电器关
        relay_count = 0;
    }else{
        relay.off();
    }
}

// 灯带呼吸
void strips_Breathe() {
    // 首次设置颜色
    for (int i = 0; i < STRIP_COUNT; i++) {
        strips[i]->setBrightness(255);
        strips[i]->fillColor(STRIP_COLOR_G, STRIP_COLOR_R, STRIP_COLOR_B);
    }

    // 渐亮
    for (int brightness = BREATHE_MIN; brightness <= BREATHE_MAX; brightness += BREATHE_STEP_VALUE) {
        // 确保不超过最大值
        int actualBrightness = (brightness > BREATHE_MAX) ? BREATHE_MAX : brightness;

        for (int i = 0; i < STRIP_COUNT; i++) {
            strips[i]->setBrightness(actualBrightness);
        }
        for (int i = 0; i < STRIP_COUNT; i++) {
            strips[i]->show();
        }
        delay(BREATHE_STEP_MS);
        relay_Control();        // 继电器控制
    }

    // 可选：在峰值处短暂停留
//    delay(100);

    // 渐暗
    for (int brightness = BREATHE_MAX; brightness >= BREATHE_MIN; brightness -= BREATHE_STEP_VALUE) {
        // 确保不低于最小值
        int actualBrightness = (brightness < BREATHE_MIN) ? BREATHE_MIN : brightness;

        for (int i = 0; i < STRIP_COUNT; i++) {
            strips[i]->setBrightness(actualBrightness);
        }
        for (int i = 0; i < STRIP_COUNT; i++) {
            strips[i]->show();
        }
        delay(BREATHE_STEP_MS);
        relay_Control();        // 继电器控制
    }

    // 可选：在谷值处短暂停留
//    delay(100);
}

// 灯带任务
void app_Task() {
//    strips_Breathe();   // 呼吸灯
    if(touchSensor.isTouched()){
        strips_Breathe();       // 呼吸灯
    }else{
        delay(100);
        relay_Control();        // 继电器控制
        strips_On();            // 灯带常亮
    }

}