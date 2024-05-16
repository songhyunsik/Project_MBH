#include <curl/curl.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// 관서번호
// 서울: 108
// 세종: 29
// 제주: 184
// 대전: 133
// 부산: 159

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
    void outputtxt();
    void findtxt();
};

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
    
    inputFile.close();
}


int main() {
    weather seoul("https://apihub.kma.go.kr/api/typ01/url/kma_sfctm2.php?tm=0&stn=108&help=0&authKey=FyIoXmJzSiWiKF5icxolng","seoul.txt");
    weather busan("https://apihub.kma.go.kr/api/typ01/url/kma_sfctm2.php?tm=0&stn=159&help=0&authKey=FyIoXmJzSiWiKF5icxolng","busan.txt");
    weather daejeon("https://apihub.kma.go.kr/api/typ01/url/kma_sfctm2.php?tm=0&stn=133&help=0&authKey=FyIoXmJzSiWiKF5icxolng","daejeon.txt");
    weather jeju("https://apihub.kma.go.kr/api/typ01/url/kma_sfctm2.php?tm=0&stn=184&help=0&authKey=FyIoXmJzSiWiKF5icxolng","jeju.txt");

    seoul.outputtxt();
    busan.outputtxt();
    daejeon.outputtxt();
    jeju.outputtxt();

    seoul.findtxt();
    busan.findtxt();
    daejeon.findtxt();
    jeju.findtxt();

    return 0;
}

