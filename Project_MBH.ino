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
      colorWipe(strip.Color(255, 0, 0), 50); // Red
      colorWipe(strip.Color(0, 255, 0), 50); // Green
      colorWipe(strip.Color(0, 0, 255), 50); // Blue
      colorWipe(strip.Color(0, 0, 0, 255), 50); // White RGBW
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
      rainbowCycle(8);
      break;
    case 5:
      theaterChaseRainbow(8);
      break;
    default:
      break;
  }

  // cnt 값을 제한 + 마지막 패턴이 도달하였을 때, 처음 패턴으로 초기화
  if (cnt > 5) {
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
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
    if(cnt != 1) {
      return;
    }
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
    if(cnt != 3) {
      return;
    }
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
    if(cnt != 4) {
      return;
    }
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
    if(cnt != 2) {
      return;
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
    if(cnt != 5) {
      return;
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
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