#include <Arduino.h>
#include "seeed/grove/ws2813_ring.h"
#include "global/GData.h"
#include "global/GObject.h"
#include "user/app.h"


void setup() {
    Serial.begin(115200);

//    strips_On();    // 灯带打开
}

void loop() {
    app_Task(); // 灯带任务
}