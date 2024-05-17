#include <curl/curl.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>

using namespace std;

class weather
{
private:
    const char* spacedata;
    const char* filename;
    
public:
    string ta;              // 기온
    string rn;              // 강수량
    string hm;              // 습도
    string ca_tot;          // 전운량
    weather(const char* data, const char* file);
    
    void outputtxt();       // API 데이터 입력
    void findtxt();         // 필요 데이터 변수 저장
};

void display();
void led();

int main() {
    string year,mon,hour,min;
    weather seoul("https://apihub.kma.go.kr/api/typ01/url/kma_sfctm2.php?tm=0&stn=108&help=0&authKey=FyIoXmJzSiWiKF5icxolng","seoul.txt");      // 서울: 108
    weather busan("https://apihub.kma.go.kr/api/typ01/url/kma_sfctm2.php?tm=0&stn=159&help=0&authKey=FyIoXmJzSiWiKF5icxolng","busan.txt");      // 부산: 159
    weather daejeon("https://apihub.kma.go.kr/api/typ01/url/kma_sfctm2.php?tm=0&stn=133&help=0&authKey=FyIoXmJzSiWiKF5icxolng","daejeon.txt");  // 대전: 133
    weather jeju("https://apihub.kma.go.kr/api/typ01/url/kma_sfctm2.php?tm=0&stn=184&help=0&authKey=FyIoXmJzSiWiKF5icxolng","jeju.txt");        // 제주: 184

    // 현재시간
    time_t now = time(nullptr);
    tm* current_time = localtime(&now);

    year = to_string(current_time->tm_year + 1900);
    mon = to_string(current_time->tm_mon + 1);
    hour = to_string(current_time->tm_hour);
    min = to_string(current_time->tm_min);

    
    while (1)
    {
        display();

    }
    
    

    // seoul.outputtxt();
    // busan.outputtxt();
    // daejeon.outputtxt();
    // jeju.outputtxt();

    // seoul.nowtime();
    // busan.nowtime();
    // daejeon.nowtime();
    // jeju.nowtime();

    // seoul.findtxt();
    // busan.findtxt();
    // daejeon.findtxt();
    // jeju.findtxt();

    return 0;
}

weather::weather(const char* data, const char* file){
    spacedata = data;
    filename = file;
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

    // 단어를 출력
    cout << "기온은: "<< ta <<  endl;
    cout << "습도는: "<<  hm <<  endl;
    cout << "강수량은: "<< rn <<  endl;
    cout << "적운량은: "<< ca_tot <<  endl;
    
    inputFile.close();
}