#include <Adafruit_NeoPixel.h>

#define PIN 6
#define SW 2
#define BRIGHTNESS_PIN A0 // 가변 저항 연결 핀
#define NUM_PIXELS 60

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);

int cnt = 0;

void colorWipe(uint32_t c, uint8_t wait);
void rainbow(uint8_t wait);
void rainbowCycle(uint8_t wait);
void theaterChase(uint32_t c, uint8_t wait);
void theaterChaseRainbow(uint8_t wait);
uint32_t Wheel(byte WheelPos);

void setup() {
  pinMode(SW, INPUT_PULLUP);

  strip.begin();
  strip.setBrightness(50);
  strip.show(); // 모든 픽셀을 꺼진 상태로 초기화
}

void loop() {
  if(digitalRead(SW) == LOW) {
    cnt++;
    delay(100); // 버튼 튀는 현상 방지를 위한 딜레이
    if(cnt > 5) cnt = 1; // 5번까지 반복 후 초기화

    switch(cnt) {
      case 1:
        colorWipe(strip.Color(255, 0, 0), 50); // Red
        colorWipe(strip.Color(0, 255, 0), 50); // Green
        colorWipe(strip.Color(0, 0, 255), 50); // Blue
        colorWipe(strip.Color(255, 255, 255), 50); // White
        break;
      case 2:
        theaterChase(strip.Color(127, 127, 127), 50); // White
        theaterChase(strip.Color(127, 0, 0), 50); // Red
        theaterChase(strip.Color(0, 0, 127), 50); // Blue
        break;
      case 3:
        rainbow(8);
        break;
      case 4:
        rainbowCycle(20);
        break;
      case 5:
        theaterChaseRainbow(10);
        break;
      default:
        break;
    }
  }
}

// 픽셀을 순서대로 색상으로 채웁니다.
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

// 무지개 색상 효과
void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// 무지개 색상이 동일하게 분포되도록 설정
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5번의 무지개 효과 사이클
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// 극장 스타일의 픽셀 이동 효과
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) { // 10번의 이동 효과
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c); // 매 3번째 픽셀 켜기
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0); // 매 3번째 픽셀 끄기
      }
    }
  }
}

// 극장 스타일의 무지개 색상 효과
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) { // 모든 256가지 색상의 무지개 효과 사이클
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255)); // 매 3번째 픽셀에 무지개 색상 적용
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0); // 매 3번째 픽셀 끄기
      }
    }
  }
}

// 0부터 255까지의 값에 따라 색상 값을 반환
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
