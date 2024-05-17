#include <curl/curl.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

String folder = "/home/hrd/Desktop/Project_MBH/data/";
string folderPath = "/home/hrd/Desktop/Project_MBH/data/";
int serial_num  = 3;

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
    void OpenCV();
    void init();
};




int main() {
    // set class 지역멤버(const char* url, const char* filename, string 지역이름, string 이미지파일이름)
    weather seoul("https://apihub.kma.go.kr/api/typ01/url/kma_sfctm2.php?tm=0&stn=108&help=0&authKey=FyIoXmJzSiWiKF5icxolng","seoul.txt","SEOUL","seoul.png");          // 서울: 108
    weather busan("https://apihub.kma.go.kr/api/typ01/url/kma_sfctm2.php?tm=0&stn=159&help=0&authKey=FyIoXmJzSiWiKF5icxolng","busan.txt","BUSAN","busan.png");          // 부산: 159
    weather daejeon("https://apihub.kma.go.kr/api/typ01/url/kma_sfctm2.php?tm=0&stn=133&help=0&authKey=FyIoXmJzSiWiKF5icxolng","daejeon.txt","DAEJEON","daejun.png" );  // 대전: 133
    weather jeju("https://apihub.kma.go.kr/api/typ01/url/kma_sfctm2.php?tm=0&stn=184&help=0&authKey=FyIoXmJzSiWiKF5icxolng","jeju.txt","JEJU","jeju.jpg");              // 제주: 184

    // 현재시간 확인
    time_t now = time(nullptr);
    tm* current_time = localtime(&now);

    // 시간 정수형 변환
    // string year,mon,hour,min;
    // year = to_string(current_time->tm_year + 1900);
    // mon = to_string(current_time->tm_mon + 1);
    // hour = to_string(current_time->tm_hour);
    // min = to_string(current_time->tm_min);

    while(1){
        // set weather value from 기상청 API
        seoul.init();
        busan.init();
        daejeon.init();
        jeju.init();

        // 정각마다 기성청 API 데이터 revalue
        if(current_time->tm_hour == 0){
            seoul.init();
            busan.init();
            daejeon.init();
            jeju.init();
        }

        switch (serial_num)
        {
        case 1:
            seoul.OpenCV();
            continue;
        case 2:
            busan.OpenCV();
            continue;
        case 3:
            daejeon.OpenCV();
            continue;
        case 4:
            jeju.OpenCV();
            continue;

        default :
            destroyAllWindows();
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



void weather::OpenCV(){

    Mat img = imread(folderPath + imgfile);      //Scalar(220, 245, 245) : 베이지색
    putText(img, name, Point(50, 30), FONT_HERSHEY_SIMPLEX, 1, Scalar(220, 245, 245), 3.0);
    // putText(img, "Today's Weather : ", Point(50, 60), FONT_HERSHEY_SIMPLEX, 1, Scalar(220, 245, 245), 2.5);
    putText(img, "Today's Temperature : " + ta, Point(50, 90), FONT_HERSHEY_SIMPLEX, 1, Scalar(220, 245, 245), 2.5);
    putText(img, "Today's Rainfall : " + rn, Point(50, 120), FONT_HERSHEY_SIMPLEX, 1, Scalar(220, 245, 245), 2.5);
    putText(img, "Today's Total Cloudiness : " + ca_tot, Point(50, 150), FONT_HERSHEY_SIMPLEX, 1, Scalar(220, 245, 245), 2.5);
       
    // 이모지 이미지 불러오기
    Mat emoji = imread(folderPath + "smile.png", IMREAD_COLOR);
    if (emoji.empty()) {
        cerr << "이모지 이미지 불러오기 실패!" << endl;
    }
    // 이모지 이미지 크기 조정
    double scale = 0.04;
    Mat resizedEmoji;
    resize(emoji, resizedEmoji, Size(), scale, scale);

    int emojiX = 340; 
    int emojiY = 30; 

    
    Rect roi(Point(emojiX, emojiY), resizedEmoji.size());
    resizedEmoji.copyTo(img(roi), resizedEmoji);

    imshow("img", img);
    waitKey(0);
}
void weather::init(){
    outputtxt();
    findtxt();
}