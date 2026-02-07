//
// Created by 99081 on 2026/2/7.
//

#include "app.h"

// 灯带常亮
void strips_On() {
    for (int i = 0; i < STRIP_COUNT; i++) {
        strips[i]->setBrightness(STRIP_BRIGHTNESS);
        strips[i]->fillColor(STRIP_COLOR_R, STRIP_COLOR_G, STRIP_COLOR_B);
        strips[i]->show();

    }
}


// 灯带任务
void app_Task() {
    strips_On();    // 灯带常亮
    delay(1000);
}