//
// Created by 99081 on 2026/2/7.
//

#include "app.h"
#include <stdlib.h>     // 用于rand()和srand()
#include <time.h>       // 用于time()

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
uint32_t relay_count = 0;           // 触摸程序循环计数
uint32_t relay_count_target = 0;    // 目标计数值(随机)
bool last_touch_state = false;      // 上一次触摸状态
bool relay_triggered = false;       // 继电器是否已被触发
void relay_Control() {
    bool current_touch = touchSensor.isTouched();

    // 触摸中，确保继电器关闭
    if(current_touch){
        relay.off();            // 继电器关
        relay_triggered = false;
        relay_count = 0;
        relay_count_target = 0;
    }
        // 检测到从触摸状态变为非触摸状态(手放开)
    else if(last_touch_state && !current_touch && !relay_triggered){
        // 生成RELAY_COUNT_MIN到RELAY_COUNT_MAX之间的随机目标值
        relay_count_target = RELAY_COUNT_MIN + (rand() % (RELAY_COUNT_MAX - RELAY_COUNT_MIN + 1));
        relay.on();             // 继电器开
        relay_triggered = true;
        relay_count = 1;
        printf("relay_count_target: %d\n", relay_count_target);
        printf("relay_count: %d\n", relay_count);
    }
        // 继电器已开启，继续计数
    else if(relay_triggered && relay_count > 0 && relay_count < relay_count_target){
        relay_count ++;
        printf("relay_count: %d\n", relay_count);
    }
        // 达到目标时长，关闭继电器
    else if(relay_count >= relay_count_target && relay_count_target > 0){
        relay.off();            // 继电器关
        relay_triggered = false;
        relay_count = 0;
        relay_count_target = 0;
        printf("Relay OFF - target reached\n");
    }

    // 更新触摸状态
    last_touch_state = current_touch;
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