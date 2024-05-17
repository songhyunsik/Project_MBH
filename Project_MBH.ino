#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 6
#define SW 2    // 버튼 연결 핀
#define BRIGHTNESS_PIN A0 // 가변 저항 연결 핀


int brightnessValue = 0; // 현재 밝기 값
int brightnessChanged  = false; // 이전 밝기 값

volatile int cnt = 0; // 인터럽트에 의해 변경되므로 volatile 선언

Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  #if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif

  pinMode(SW, INPUT_PULLUP);  // 버튼 핀을 풀업 입력 모드로 설정

  strip.begin();
  strip.setBrightness(50);
  Off(strip.Color(0, 0, 0), 50); // Off
  strip.show(); // 모든 픽셀이 꺼져있는 상태로 출력
  Serial.begin(115200);

  // 인터럽트 설정 (버튼 핀에 FALLING 모드 설정)
  attachInterrupt(digitalPinToInterrupt(SW), buttonISR, FALLING);
}

void loop() {
  brightnessValue = map(analogRead(BRIGHTNESS_PIN), 0, 1023, 0, 255); // 아날로그 입력 값을 밝기로 변환
  strip.setBrightness(brightnessValue); // NeoPixel의 밝기를 설정
  Serial.print("Mode: "); 
  Serial.println(cnt);

   // 현재 밝기 값이 이전 값과 다르면 작업을 수행
  if (brightnessChanged ) {
    // NeoPixel의 밝기를 설정
    strip.setBrightness(brightnessValue);

    // 이전 밝기 값을 업데이트
    brightnessChanged  = false;
  }
 // 변경된 밝기 값 출력
  Serial.print("Brightness: ");
  Serial.println(brightnessValue); 

  // cnt 값에 따라 LED 패턴 실행
  switch (cnt) {
    case 1:
      BUSAN_COLOR(strip.Color(0, 0, 127), 50); // Blue
      break;
    case 2:
      DAEJEON_COLOR(strip.Color(255, 0, 255), 50); // Purple
      break;
    case 3:
      JEJU_COLOR(strip.Color(255, 255, 0), 50); // Yellow
      break;
    case 4:
      SEOUL_COLOR(strip.Color(0, 0, 127), 50); // Blue
      break;
    default:
      Off(strip.Color(0, 0, 0), 50); // Off
      break;
  }

  // cnt 값을 제한 + 마지막 패턴이 도달하였을 때, 처음 패턴으로 초기화
  if (cnt > 4) {
    cnt = 0;
  }

  // 작은 지연 추가하여 CPU 과부하 방지
  delay(10);
}

// 인터럽트 서비스 루틴 (ISR)
void buttonISR() {
  cnt++;
}

// Fill the dots one after the other with a color
void Off(uint32_t c, uint8_t wait) {
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
  }
  strip.show();
  delay(wait);
  if(cnt != 0) {
    return;
  }
}

void BUSAN_COLOR(uint32_t c, uint8_t wait) {
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
  }
  strip.show();
  delay(wait);
  if(cnt != 1) {
    return;
  }
}

void DAEJEON_COLOR(uint32_t c, uint8_t wait) {
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
  }
  strip.show();
  delay(wait);
  if(cnt != 2) {
    return;
  }
}

void JEJU_COLOR(uint32_t c, uint8_t wait) {
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
  }
  strip.show();
  delay(wait);
  if(cnt != 3) {
    return;
  }
}

void SEOUL_COLOR(uint32_t c, uint8_t wait) {
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
  }
  strip.show();
  delay(wait);
  if(cnt != 4) {
    return;
  }
}
