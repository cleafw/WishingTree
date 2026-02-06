/**
 * @file sm16703_strip.cpp
 * @brief SM16703 LED灯带驱动实现
 */

#include "sm16703_strip.h"

// 构造函数 - 只需数据引脚
SM16703Strip::SM16703Strip(uint8_t data, uint16_t numPixels)
        : dataPin(data), numLEDs(numPixels), brightness(255),
          powerPin(255), hasPowerControl(false) {
    leds = new CRGB[numPixels];
}

// 构造函数 - 带电源控制引脚
SM16703Strip::SM16703Strip(uint8_t data, uint8_t power, uint16_t numPixels, bool usePower)
        : dataPin(data), powerPin(power), numLEDs(numPixels),
          brightness(255), hasPowerControl(usePower) {
    leds = new CRGB[numPixels];
}

// 析构函数
SM16703Strip::~SM16703Strip() {
    if (leds) {
        delete[] leds;
    }
}

// 初始化LED灯带
void SM16703Strip::begin() {
    // 配置电源控制引脚
    if (hasPowerControl && powerPin != 255) {
        pinMode(powerPin, OUTPUT);
        digitalWrite(powerPin, HIGH);
    }

    // 初始化FastLED
#if defined(ESP32) || defined(ESP8266)
    switch(dataPin) {
        case D0:  FastLED.addLeds<SM16703, D0,  RGB>(leds, numLEDs); break;
        case D1:  FastLED.addLeds<SM16703, D1,  RGB>(leds, numLEDs); break;
        case D2:  FastLED.addLeds<SM16703, D2,  RGB>(leds, numLEDs); break;
        case D3:  FastLED.addLeds<SM16703, D3,  RGB>(leds, numLEDs); break;
        case D4:  FastLED.addLeds<SM16703, D4,  RGB>(leds, numLEDs); break;
        case D5:  FastLED.addLeds<SM16703, D5,  RGB>(leds, numLEDs); break;
        case D6:  FastLED.addLeds<SM16703, D6,  RGB>(leds, numLEDs); break;
        case D7:  FastLED.addLeds<SM16703, D7,  RGB>(leds, numLEDs); break;
        case D8:  FastLED.addLeds<SM16703, D8,  RGB>(leds, numLEDs); break;
        case D9:  FastLED.addLeds<SM16703, D9,  RGB>(leds, numLEDs); break;
        case D10: FastLED.addLeds<SM16703, D10, RGB>(leds, numLEDs); break;
        default:  FastLED.addLeds<SM16703, D4,  RGB>(leds, numLEDs); break;
    }
#else
    FastLED.addLeds<SM16703, 4, RGB>(leds, numLEDs);
#endif

    FastLED.setCorrection(TypicalLEDStrip);
    FastLED.setDither(true);
    FastLED.setBrightness(brightness);

    clear();
    show();
}

void SM16703Strip::setBrightness(uint8_t bright) {
    brightness = bright;
    FastLED.setBrightness(bright);
}

void SM16703Strip::clear() {
    fill_solid(leds, numLEDs, CRGB::Black);
}

void SM16703Strip::show() {
    FastLED.show();
}

void SM16703Strip::powerOn() {
    if (hasPowerControl && powerPin != 255) {
        digitalWrite(powerPin, HIGH);
    }
}

void SM16703Strip::powerOff() {
    if (hasPowerControl && powerPin != 255) {
        digitalWrite(powerPin, LOW);
    }
}

void SM16703Strip::setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b) {
    if (n < numLEDs) {
        leds[n] = CRGB(r, g, b);
    }
}

void SM16703Strip::setPixelColor(uint16_t n, CRGB color) {
    if (n < numLEDs) {
        leds[n] = color;
    }
}

void SM16703Strip::fillColor(uint8_t r, uint8_t g, uint8_t b) {
    fill_solid(leds, numLEDs, CRGB(r, g, b));
}

void SM16703Strip::fillColor(CRGB color) {
    fill_solid(leds, numLEDs, color);
}

void SM16703Strip::fillRange(uint16_t start, uint16_t count, uint8_t r, uint8_t g, uint8_t b) {
    fillRange(start, count, CRGB(r, g, b));
}

void SM16703Strip::fillRange(uint16_t start, uint16_t count, CRGB color) {
    if (start < numLEDs) {
        uint16_t end = (start + count < numLEDs) ? (start + count) : numLEDs;
        fill_solid(leds + start, end - start, color);
    }
}

void SM16703Strip::colorWipe(uint8_t r, uint8_t g, uint8_t b, uint8_t wait) {
    colorWipe(CRGB(r, g, b), wait);
}

void SM16703Strip::colorWipe(CRGB color, uint8_t wait) {
    for (uint16_t i = 0; i < numLEDs; i++) {
        leds[i] = color;
        show();
        delay(wait);
    }
}

void SM16703Strip::rainbow(uint8_t wait) {
    for (uint16_t j = 0; j < 256; j++) {
        for (uint16_t i = 0; i < numLEDs; i++) {
            leds[i] = wheel((i + j) & 255);
        }
        show();
        delay(wait);
    }
}

void SM16703Strip::rainbowCycle(uint8_t wait, uint8_t cycles) {
    for (uint16_t j = 0; j < 256 * cycles; j++) {
        for (uint16_t i = 0; i < numLEDs; i++) {
            leds[i] = wheel(((i * 256 / numLEDs) + j) & 255);
        }
        show();
        delay(wait);
    }
}

void SM16703Strip::theaterChase(uint8_t r, uint8_t g, uint8_t b, uint8_t wait) {
    theaterChase(CRGB(r, g, b), wait);
}

void SM16703Strip::theaterChase(CRGB color, uint8_t wait) {
    for (int j = 0; j < 10; j++) {
        for (int q = 0; q < 3; q++) {
            for (uint16_t i = 0; i < numLEDs; i += 3) {
                leds[i + q] = color;
            }
            show();
            delay(wait);

            for (uint16_t i = 0; i < numLEDs; i += 3) {
                leds[i + q] = CRGB::Black;
            }
        }
    }
}

void SM16703Strip::theaterChaseRainbow(uint8_t wait) {
    for (int j = 0; j < 256; j++) {
        for (int q = 0; q < 3; q++) {
            for (uint16_t i = 0; i < numLEDs; i += 3) {
                leds[i + q] = wheel((i + j) % 255);
            }
            show();
            delay(wait);

            for (uint16_t i = 0; i < numLEDs; i += 3) {
                leds[i + q] = CRGB::Black;
            }
        }
    }
}

void SM16703Strip::breathe(uint8_t r, uint8_t g, uint8_t b, uint8_t wait) {
    breathe(CRGB(r, g, b), wait);
}

void SM16703Strip::breathe(CRGB color, uint8_t wait) {
    // 渐亮
    for (int brightness = 0; brightness <= 255; brightness++) {
        // 直接计算每个颜色分量
        uint8_t r = (color.r * brightness) / 255;
        uint8_t g = (color.g * brightness) / 255;
        uint8_t b = (color.b * brightness) / 255;

        fillColor(r, g, b);
        show();
        delay(wait);
    }

    // 渐暗
    for (int brightness = 255; brightness >= 0; brightness--) {
        // 直接计算每个颜色分量
        uint8_t r = (color.r * brightness) / 255;
        uint8_t g = (color.g * brightness) / 255;
        uint8_t b = (color.b * brightness) / 255;

        fillColor(r, g, b);
        show();
        delay(wait);
    }
}

void SM16703Strip::rotate(uint8_t r, uint8_t g, uint8_t b, uint8_t wait) {
    rotate(CRGB(r, g, b), wait);
}

void SM16703Strip::rotate(CRGB color, uint8_t wait) {
    for (uint16_t j = 0; j < numLEDs; j++) {
        clear();
        leds[j] = color;
        show();
        delay(wait);
    }
}

void SM16703Strip::flow(uint8_t r, uint8_t g, uint8_t b, uint8_t length, uint8_t wait) {
    flow(CRGB(r, g, b), length, wait);
}

void SM16703Strip::flow(CRGB color, uint8_t length, uint8_t wait) {
    for (uint16_t j = 0; j < numLEDs + length; j++) {
        clear();
        for (uint8_t i = 0; i < length; i++) {
            if (j >= i && j - i < numLEDs) {
                leds[j - i] = color;
                leds[j - i].nscale8(255 - (i * 255 / length));
            }
        }
        show();
        delay(wait);
    }
}

void SM16703Strip::blink(uint8_t r, uint8_t g, uint8_t b, uint8_t times, uint16_t interval) {
    blink(CRGB(r, g, b), times, interval);
}

void SM16703Strip::blink(CRGB color, uint8_t times, uint16_t interval) {
    for (uint8_t i = 0; i < times; i++) {
        fillColor(color);
        show();
        delay(interval);
        clear();
        show();
        delay(interval);
    }
}

void SM16703Strip::gradientFill(uint8_t r1, uint8_t g1, uint8_t b1,
                                uint8_t r2, uint8_t g2, uint8_t b2) {
    gradientFill(CRGB(r1, g1, b1), CRGB(r2, g2, b2));
}

void SM16703Strip::gradientFill(CRGB color1, CRGB color2) {
    // 手动实现渐变（最可靠的方法）
    for (uint16_t i = 0; i < numLEDs; i++) {
        // 计算混合比例 (0-255)
        uint8_t blendAmount = map(i, 0, numLEDs - 1, 0, 255);

        // 手动混合两个颜色
        leds[i].r = map(blendAmount, 0, 255, color1.r, color2.r);
        leds[i].g = map(blendAmount, 0, 255, color1.g, color2.g);
        leds[i].b = map(blendAmount, 0, 255, color1.b, color2.b);
    }
}

void SM16703Strip::scanner(uint8_t r, uint8_t g, uint8_t b, uint8_t width, uint8_t wait) {
    scanner(CRGB(r, g, b), width, wait);
}

void SM16703Strip::scanner(CRGB color, uint8_t width, uint8_t wait) {
    for (int i = 0; i < numLEDs - width; i++) {
        clear();
        for (uint8_t j = 0; j < width; j++) {
            leds[i + j] = color;
            leds[i + j].nscale8(255 - (j * 200 / width));
        }
        show();
        delay(wait);
    }

    for (int i = numLEDs - width; i >= 0; i--) {
        clear();
        for (uint8_t j = 0; j < width; j++) {
            leds[i + j] = color;
            leds[i + j].nscale8(255 - (j * 200 / width));
        }
        show();
        delay(wait);
    }
}

void SM16703Strip::fire(uint8_t cooling, uint8_t sparking, uint8_t wait) {
    static byte heat[SM16703_DEFAULT_NUM_LEDS];

    for (int loops = 0; loops < 100; loops++) {
        for (int i = 0; i < numLEDs; i++) {
            heat[i] = qsub8(heat[i], random(0, ((cooling * 10) / numLEDs) + 2));
        }

        for (int k = numLEDs - 1; k >= 2; k--) {
            heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
        }

        if (random(255) < sparking) {
            int y = random(7);
            heat[y] = qadd8(heat[y], random(160, 255));
        }

        for (int j = 0; j < numLEDs; j++) {
            leds[j] = HeatColor(heat[j]);
        }

        show();
        delay(wait);
    }
}

void SM16703Strip::lightning(uint8_t flashes) {
    for (uint8_t i = 0; i < flashes; i++) {
        fillColor(255, 255, 255);
        show();
        delay(random(10, 50));

        clear();
        show();
        delay(random(50, 150));

        fillColor(200, 200, 255);
        show();
        delay(random(50, 100));

        clear();
        show();
        delay(random(100, 500));
    }
}

uint16_t SM16703Strip::numPixels() const {
    return numLEDs;
}

CRGB SM16703Strip::getPixelColor(uint16_t n) const {
    if (n < numLEDs) {
        return leds[n];
    }
    return CRGB::Black;
}

CRGB* SM16703Strip::getLEDs() {
    return leds;
}

CRGB SM16703Strip::wheel(uint8_t wheelPos) {
    wheelPos = 255 - wheelPos;
    if (wheelPos < 85) {
        return CRGB(255 - wheelPos * 3, 0, wheelPos * 3);
    }
    if (wheelPos < 170) {
        wheelPos -= 85;
        return CRGB(0, wheelPos * 3, 255 - wheelPos * 3);
    }
    wheelPos -= 170;
    return CRGB(wheelPos * 3, 255 - wheelPos * 3, 0);
}