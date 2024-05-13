#include <Adafruit_NeoPixel.h>
#include <wiringPi.h>

#define PIN 6
#define SW 2
#define BRIGHTNESS_PIN 0 // 가변 저항 연결 핀 (아날로그 핀 사용 불가능)

int cnt = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  wiringPiSetup(); // wiringPi 라이브러리를 초기화합니다.
  pinMode(SW, INPUT);

  strip.begin();
  strip.setBrightness(50);
  strip.show(); // Initialize all pixels to 'off'
  if (wiringPiISR(SW, INT_EDGE_FALLING, &incrementCounter) < 0) { // 스위치 인터럽트를 설정합니다.
    printf("Unable to setup ISR\n");
    return 1;
  }
}

void loop() {
  int brightnessValue = map(analogRead(BRIGHTNESS_PIN), 0, 1023, 0, 255); // 아날로그 입력 값을 밝기로 변환합니다.
  strip.setBrightness(brightnessValue); // NeoPixel의 밝기를 설정합니다.

  if(cnt == 1) {
    colorWipe(strip.Color(255, 0, 0), 50); // Red
    colorWipe(strip.Color(0, 255, 0), 50); // Green
    colorWipe(strip.Color(0, 0, 255), 50); // Blue
    colorWipe(strip.Color(0, 0, 0, 255), 50); // White RGBW
  }

  else if(cnt == 2) {
    theaterChase(strip.Color(127, 127, 127), 50); // White
    theaterChase(strip.Color(127, 0, 0), 50); // Red
    theaterChase(strip.Color(0, 0, 127), 50); // Blue
  }

  else if(cnt == 3) {
    rainbow(8);
  }

  else if(cnt == 4) {
    rainbowCycle(20);
  }

  else if(cnt == 5) {
    theaterChaseRainbow(10);
  }
}

void incrementCounter() {
  cnt++;
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
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

      for (uint16_t i=0; i < strip.numPixels(); i