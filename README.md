# Project_MBH
고려 HRD 개발자 양성과정 프로젝트

### 개발자 양성과정 프로젝트
일자 : 2024.05.11 ~ 05.17

### 개요

   - 디스플레이 데이터 출력
   - wifi를 통한 데이터 기입
   - LED Strip 색상 및 밝기 조절


### 작동원리
   - 기상청 API를 통해서 활용
   - 해당 데이터를 OpenCV를 통해서 화면 출력
   - 주변 인테리어
      - Led Strip를 통해 색상 및 밝기 출력


### Led Strip
   - WS2812b strips contain RGB LEDs
   - The 5V LEDs in the WS2812b strips work well with the Arduino Uno we're using for our projects
   - pins: Power5V, Data In Din, and Ground 0V
     - Red : 5V / Green : Data Out / White : GND


### 날씨데이터 활용
   1. 날씨정보가 올라오는 HTML 화면을 확보해야함
   2. curl를 가지고 데이터를 긁어와서 날씨정보를 얻어야 함.
   3. txt파일에 데이터 기입
   4. 원하는 데이터 추출
      - 기온, 적운량, 습도, 풍속

   - 블로그나 기존에 진행했던 프로젝트를 참고.
   - chat gpt 활용

   --------------------------------------------------------------------
   날씨 데이터 활용 시 한글 깨짐 현상
   1. 기상청 API데이터 인코딩 EUR-KR
   2. OpenCV 활용 인코딩 > UTF-8
   3. API데이터를 UTF-8인코딩 가능한 데이터로 변환 후 데이터 가공(inconv.h)

### 시간
   1. ctime라이브러리 활용
   2. 년도, 월, 일, 시간, 분, 초 계산 후 저장





