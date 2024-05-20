#include <curl/curl.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

string folderPath = "/home/pi/Desktop/Project_MBH/data/";

class weather
{
private:
    const char* spacedata;
    const char* filename;
    string imgfile;
    
public:
    string ta;              // 기온
    string rn;              // 강수량
    string hm;              // 습도
    string ca_tot;          // 전운량
    string name;
    weather(const char* data, const char* file, string name_value,string fileimg);
    
    void outputtxt();       // API 데이터 입력
    void findtxt();         // 필요 데이터 변수 저장
    void OpenCV(string H,string M);
    void init();

};





int main() {
    // set 지역 (const char* url, const char* filename, string 지역이름, string 이미지파일이름)
    // 서울: 108, 부산: 159, 대전: 133, 제주: 184
    weather seoul("https://apihub.kma.go.kr/api/typ01/url/kma_sfctm2.php?tm=0&stn=108&help=0&authKey=FyIoXmJzSiWiKF5icxolng","seoul.txt","SEOUL","seoul.jpg");
    weather busan("https://apihub.kma.go.kr/api/typ01/url/kma_sfctm2.php?tm=0&stn=159&help=0&authKey=FyIoXmJzSiWiKF5icxolng","busan.txt","BUSAN","busan.jpg");
    weather daejeon("https://apihub.kma.go.kr/api/typ01/url/kma_sfctm2.php?tm=0&stn=133&help=0&authKey=FyIoXmJzSiWiKF5icxolng","daejeon.txt","DAEJEON","daejun.png" );
    weather jeju("https://apihub.kma.go.kr/api/typ01/url/kma_sfctm2.php?tm=0&stn=184&help=0&authKey=FyIoXmJzSiWiKF5icxolng","jeju.txt","JEJU","jeju.jpg");

    // 지역확인 변수
    int button = 0;
    string hour,min;

    // init : set weather value from 기상청 API
    seoul.init();
    busan.init();
    daejeon.init();
    jeju.init();

	while(1){
//		button = ???;
		switch(button){
		case 0:
			while(1){
				time_t now = time(nullptr);
				tm* current_time = localtime(&now);
				min = to_string(current_time->tm_min);
				hour = to_string(current_time->tm_hour);
				if(current_time->tm_min == 0){
					seoul.init();
				}
				seoul.OpenCV(hour,min);
				waitKey(1000);
				continue;
			}
		case 1:
			while(1){
				time_t now = time(nullptr);
				tm* current_time = localtime(&now);
				min = to_string(current_time->tm_min);		
				hour = to_string(current_time->tm_hour);
				if(current_time->tm_min == 0){
					busan.init();
				}
				busan.OpenCV(hour,min);
				waitKey(1000);
				continue;
			}
		case 2:
			while(1){
				time_t now = time(nullptr);
				tm* current_time = localtime(&now);
				min = to_string(current_time->tm_min);		
				hour = to_string(current_time->tm_hour);
				if(current_time->tm_min == 0){
					daejeon.init();
				}
				daejeon.OpenCV(hour,min);
				waitKey(1000);
				continue;
			}
		case 3:
			while(1){
				time_t now = time(nullptr);
				tm* current_time = localtime(&now);
				min = to_string(current_time->tm_min);		
				hour = to_string(current_time->tm_hour);
				if(current_time->tm_min == 0){
					jeju.init();
				}
				jeju.OpenCV(hour,min);
				waitKey(1000);
				continue;
			}
		
		}
	}

    return 0;
}

weather::weather(const char* data, const char* file, string name_value, string fileimg){
    name = name_value;
    spacedata = data;
    filename = file;
    imgfile = fileimg;
}

void weather::outputtxt()
{
    CURL* curl = curl_easy_init();
    if(curl){
    FILE* fp = fopen(filename, "wb");
    const char* url = spacedata ; // 
    curl_easy_setopt(curl, CURLOPT_URL, url); // URL 설정
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp); // 데이터 쓰기 설정
    CURLcode res = curl_easy_perform(curl); // 데이터 다운로드 수행
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res)); // 오류 처리
    }
    curl_easy_cleanup(curl); // CURL 정리
    fclose(fp); // 파일 닫기
    }
}

void weather::init(){
    outputtxt();
    findtxt();
}

void weather::findtxt(){
    ifstream inputFile(filename); // 파일 경로를 수정하세요
    string line;

    // 파일을 한 줄씩 읽어서 특정 줄과 특정 단어를 추출
    int currentLine = 0;
    while (std::getline(inputFile, line)) {
        currentLine++;

        // 5번째 줄인 경우
        if (currentLine == 5) {
            std::istringstream iss(line);
            std::string word;
            int wordCount = 0;

            // 공백을 구분자로 하여 단어 추출
            while (iss >> word) {
                wordCount++;
                //12번째 단어
                if (wordCount == 12) {
                    ta = word;
                    continue;
                }
                // 14번째 단어
                if (wordCount == 14) {
                    hm = word;
                    continue;
                }
                //16번째 단어
                if (wordCount == 16) {                 
                    rn = word;
                    continue;
                }
                //28번째 단어
                if (wordCount == 26) {
                    ca_tot = word;
                    break;
                }
            }

            break;
        }
    }

    
    
    inputFile.close();
}



void weather::OpenCV(string H,string M){

    Mat img = imread(folderPath + imgfile);      //Scalar(220, 245, 245) : 베이지색
    // 날씨 데이터 화면 표기
    putText(img, "Today's Temperature : " + ta, Point(50, 30), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(220, 245, 245), 1.8);
    putText(img, "Today's Rainfall : " + rn, Point(50,50), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(220, 245, 245), 1.8);
    putText(img, "Today's Total Cloudiness : " + ca_tot, Point(50, 70), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(220, 245, 245), 1.8);
    
    // 시간 데이터 화면 표기
    putText(img, H+" : "+M, Point(400, 30), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(220, 245, 245), 2.8);
       

    // window fullscreen resize
    string windowName = "original image";
    namedWindow(windowName,WINDOW_NORMAL);
    setWindowProperty(windowName,WND_PROP_FULLSCREEN,WINDOW_FULLSCREEN);
    resizeWindow(windowName,1280,800);	// rasberry pi 4 display size = (1280,800)
    
    // print display
    imshow(windowName, img);
}



