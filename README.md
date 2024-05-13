# Project_MBH
고려 HRD 개발자 양성과정 프로젝트

### 개발자 양성과정 프로젝트
일자 : 2024.05.11 ~ 05.17

### 개요

   - 디스플레이 데이터 출력
   - wifi를 통한 데이터 기입
   - LED Strip 색상 및 밝기 조절


### 작동원리
   - wifi를 통한 날씨와 시간 출력
   - 
   



### Led Strip
   - WS2812b strips contain RGB LEDs
   - The 5V LEDs in the WS2812b strips work well with the Arduino Uno we're using for our projects
   - pins: Power5V, Data In Din, and Ground 0V
     - Red : 5V / Green : Data Out / White : GND


### 날씨데이터 활용
   1. 날씨정보가 올라오는 HTML 화면을 확보해야함
   2. curl를 가지고 데이터를 긁어와서 날씨정보를 얻어야 함.
   3. 데이터를 가지고 활용

   - 블로그나 기존에 진행했던 프로젝트를 참고.
